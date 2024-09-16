static void nfs4_free_openowner(struct nfs4_stateowner *so)
{
	struct nfs4_openowner *oo = openowner(so);

	kmem_cache_free(openowner_slab, oo);
}
