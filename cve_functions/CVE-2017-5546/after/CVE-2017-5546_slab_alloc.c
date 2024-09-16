slab_alloc(struct kmem_cache *cachep, gfp_t flags, unsigned long caller)
{
	unsigned long save_flags;
	void *objp;

	flags &= gfp_allowed_mask;
	cachep = slab_pre_alloc_hook(cachep, flags);
	if (unlikely(!cachep))
		return NULL;

	cache_alloc_debugcheck_before(cachep, flags);
	local_irq_save(save_flags);
	objp = __do_cache_alloc(cachep, flags);
	local_irq_restore(save_flags);
	objp = cache_alloc_debugcheck_after(cachep, flags, objp, caller);
	prefetchw(objp);

	if (unlikely(flags & __GFP_ZERO) && objp)
		memset(objp, 0, cachep->object_size);

	slab_post_alloc_hook(cachep, flags, 1, &objp);
	return objp;
}
