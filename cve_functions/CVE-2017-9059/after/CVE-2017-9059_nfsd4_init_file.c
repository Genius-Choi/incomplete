static void nfsd4_init_file(struct knfsd_fh *fh, unsigned int hashval,
				struct nfs4_file *fp)
{
	lockdep_assert_held(&state_lock);

	atomic_set(&fp->fi_ref, 1);
	spin_lock_init(&fp->fi_lock);
	INIT_LIST_HEAD(&fp->fi_stateids);
	INIT_LIST_HEAD(&fp->fi_delegations);
	INIT_LIST_HEAD(&fp->fi_clnt_odstate);
	fh_copy_shallow(&fp->fi_fhandle, fh);
	fp->fi_deleg_file = NULL;
	fp->fi_had_conflict = false;
	fp->fi_share_deny = 0;
	memset(fp->fi_fds, 0, sizeof(fp->fi_fds));
	memset(fp->fi_access, 0, sizeof(fp->fi_access));
#ifdef CONFIG_NFSD_PNFS
	INIT_LIST_HEAD(&fp->fi_lo_states);
	atomic_set(&fp->fi_lo_recalls, 0);
#endif
	hlist_add_head_rcu(&fp->fi_hash, &file_hashtbl[hashval]);
}
