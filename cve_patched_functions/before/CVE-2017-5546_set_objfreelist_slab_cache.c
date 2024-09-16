static bool set_objfreelist_slab_cache(struct kmem_cache *cachep,
			size_t size, unsigned long flags)
{
	size_t left;

	cachep->num = 0;

	if (cachep->ctor || flags & SLAB_DESTROY_BY_RCU)
		return false;

	left = calculate_slab_order(cachep, size,
			flags | CFLGS_OBJFREELIST_SLAB);
	if (!cachep->num)
		return false;

	if (cachep->num * sizeof(freelist_idx_t) > cachep->object_size)
		return false;

	cachep->colour = left / cachep->colour_off;

	return true;
}
