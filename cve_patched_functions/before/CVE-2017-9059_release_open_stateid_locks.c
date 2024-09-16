static void release_open_stateid_locks(struct nfs4_ol_stateid *open_stp,
				       struct list_head *reaplist)
{
	struct nfs4_ol_stateid *stp;

	lockdep_assert_held(&open_stp->st_stid.sc_client->cl_lock);

	while (!list_empty(&open_stp->st_locks)) {
		stp = list_entry(open_stp->st_locks.next,
				struct nfs4_ol_stateid, st_locks);
		WARN_ON(!unhash_lock_stateid(stp));
		put_ol_stateid_locked(stp, reaplist);
	}
}
