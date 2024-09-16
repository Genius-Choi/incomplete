static bool unhash_ol_stateid(struct nfs4_ol_stateid *stp)
{
	struct nfs4_file *fp = stp->st_stid.sc_file;

	lockdep_assert_held(&stp->st_stateowner->so_client->cl_lock);

	if (list_empty(&stp->st_perfile))
		return false;

	spin_lock(&fp->fi_lock);
	list_del_init(&stp->st_perfile);
	spin_unlock(&fp->fi_lock);
	list_del(&stp->st_perstateowner);
	return true;
}
