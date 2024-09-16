static void nfs4_free_ol_stateid(struct nfs4_stid *stid)
{
	struct nfs4_ol_stateid *stp = openlockstateid(stid);

	put_clnt_odstate(stp->st_clnt_odstate);
	release_all_access(stp);
	if (stp->st_stateowner)
		nfs4_put_stateowner(stp->st_stateowner);
	kmem_cache_free(stateid_slab, stid);
}
