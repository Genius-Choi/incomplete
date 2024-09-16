static bool unhash_open_stateid(struct nfs4_ol_stateid *stp,
				struct list_head *reaplist)
{
	bool unhashed;

	lockdep_assert_held(&stp->st_stid.sc_client->cl_lock);

	unhashed = unhash_ol_stateid(stp);
	release_open_stateid_locks(stp, reaplist);
	return unhashed;
}
