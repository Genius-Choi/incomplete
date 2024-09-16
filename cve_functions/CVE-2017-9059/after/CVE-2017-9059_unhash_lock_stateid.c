static bool unhash_lock_stateid(struct nfs4_ol_stateid *stp)
{
	lockdep_assert_held(&stp->st_stid.sc_client->cl_lock);

	list_del_init(&stp->st_locks);
	nfs4_unhash_stid(&stp->st_stid);
	return unhash_ol_stateid(stp);
}
