mempool_t *biovec_create_pool(int pool_entries)
{
	struct biovec_slab *bp = bvec_slabs + BVEC_POOL_MAX;

	return mempool_create_slab_pool(pool_entries, bp->slab);
}
