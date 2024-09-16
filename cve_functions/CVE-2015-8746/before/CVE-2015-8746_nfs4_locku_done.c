static void nfs4_locku_done(struct rpc_task *task, void *data)
{
	struct nfs4_unlockdata *calldata = data;

	if (!nfs4_sequence_done(task, &calldata->res.seq_res))
		return;
	switch (task->tk_status) {
		case 0:
			renew_lease(calldata->server, calldata->timestamp);
			do_vfs_lock(calldata->lsp->ls_state->inode, &calldata->fl);
			if (nfs4_update_lock_stateid(calldata->lsp,
					&calldata->res.stateid))
				break;
		case -NFS4ERR_BAD_STATEID:
		case -NFS4ERR_OLD_STATEID:
		case -NFS4ERR_STALE_STATEID:
		case -NFS4ERR_EXPIRED:
			if (!nfs4_stateid_match(&calldata->arg.stateid,
						&calldata->lsp->ls_stateid))
				rpc_restart_call_prepare(task);
			break;
		default:
			if (nfs4_async_handle_error(task, calldata->server,
						    NULL, NULL) == -EAGAIN)
				rpc_restart_call_prepare(task);
	}
	nfs_release_seqid(calldata->arg.seqid);
}
