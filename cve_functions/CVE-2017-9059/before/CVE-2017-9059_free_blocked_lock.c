free_blocked_lock(struct nfsd4_blocked_lock *nbl)
{
	locks_release_private(&nbl->nbl_lock);
	kfree(nbl);
}
