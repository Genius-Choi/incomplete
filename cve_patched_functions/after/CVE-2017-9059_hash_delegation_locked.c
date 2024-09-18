hash_delegation_locked(struct nfs4_delegation *dp, struct nfs4_file *fp)
{
	int status;
	struct nfs4_client *clp = dp->dl_stid.sc_client;

	lockdep_assert_held(&state_lock);
	lockdep_assert_held(&fp->fi_lock);

	status = nfs4_get_existing_delegation(clp, fp);
	if (status)
		return status;
	++fp->fi_delegees;
	atomic_inc(&dp->dl_stid.sc_count);
	dp->dl_stid.sc_type = NFS4_DELEG_STID;
	list_add(&dp->dl_perfile, &fp->fi_delegations);
	list_add(&dp->dl_perclnt, &clp->cl_delegations);
	return 0;
}
