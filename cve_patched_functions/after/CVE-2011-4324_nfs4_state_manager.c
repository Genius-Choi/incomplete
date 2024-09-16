static void nfs4_state_manager(struct nfs_client *clp)
{
	int status = 0;

	/* Ensure exclusive access to NFSv4 state */
	for(;;) {
		if (test_and_clear_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state)) {
			/* We're going to have to re-establish a clientid */
			status = nfs4_reclaim_lease(clp);
			if (status) {
				set_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state);
				if (status == -EAGAIN)
					continue;
				goto out_error;
			}
			clear_bit(NFS4CLNT_CHECK_LEASE, &clp->cl_state);
		}

		if (test_and_clear_bit(NFS4CLNT_CHECK_LEASE, &clp->cl_state)) {
			status = nfs4_check_lease(clp);
			if (status != 0)
				continue;
		}

		/* First recover reboot state... */
		if (test_and_clear_bit(NFS4CLNT_RECLAIM_REBOOT, &clp->cl_state)) {
			status = nfs4_do_reclaim(clp, &nfs4_reboot_recovery_ops);
			if (status == -NFS4ERR_STALE_CLIENTID)
				continue;
			nfs4_state_end_reclaim_reboot(clp);
			continue;
		}

		/* Now recover expired state... */
		if (test_and_clear_bit(NFS4CLNT_RECLAIM_NOGRACE, &clp->cl_state)) {
			status = nfs4_do_reclaim(clp, &nfs4_nograce_recovery_ops);
			if (status < 0) {
				set_bit(NFS4CLNT_RECLAIM_NOGRACE, &clp->cl_state);
				if (status == -NFS4ERR_STALE_CLIENTID)
					continue;
				if (status == -NFS4ERR_EXPIRED)
					continue;
				goto out_error;
			} else
				nfs4_state_end_reclaim_nograce(clp);
			continue;
		}

		if (test_and_clear_bit(NFS4CLNT_DELEGRETURN, &clp->cl_state)) {
			nfs_client_return_marked_delegations(clp);
			continue;
		}

		nfs4_clear_state_manager_bit(clp);
		/* Did we race with an attempt to give us more work? */
		if (clp->cl_state == 0)
			break;
		if (test_and_set_bit(NFS4CLNT_MANAGER_RUNNING, &clp->cl_state) != 0)
			break;
	}
	return;
out_error:
	printk(KERN_WARNING "Error: state manager failed on NFSv4 server %s"
			" with error %d\n", clp->cl_hostname, -status);
	if (test_bit(NFS4CLNT_RECLAIM_REBOOT, &clp->cl_state))
		nfs4_state_end_reclaim_reboot(clp);
	nfs4_clear_state_manager_bit(clp);
}
