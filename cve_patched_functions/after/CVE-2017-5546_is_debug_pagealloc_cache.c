static bool is_debug_pagealloc_cache(struct kmem_cache *cachep)
{
	if (debug_pagealloc_enabled() && OFF_SLAB(cachep) &&
		(cachep->size % PAGE_SIZE) == 0)
		return true;

	return false;
}
