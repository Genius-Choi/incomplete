static inline void *alloc_stateowner(struct kmem_cache *slab, struct xdr_netobj *owner, struct nfs4_client *clp)
{
	struct nfs4_stateowner *sop;

	sop = kmem_cache_alloc(slab, GFP_KERNEL);
	if (!sop)
		return NULL;

	sop->so_owner.data = kmemdup(owner->data, owner->len, GFP_KERNEL);
	if (!sop->so_owner.data) {
		kmem_cache_free(slab, sop);
		return NULL;
	}
	sop->so_owner.len = owner->len;

	INIT_LIST_HEAD(&sop->so_stateids);
	sop->so_client = clp;
	init_nfs4_replay(&sop->so_replay);
	atomic_set(&sop->so_count, 1);
	return sop;
}
