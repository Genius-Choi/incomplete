cache_alloc_debugcheck_after_bulk(struct kmem_cache *s, gfp_t flags,
				  size_t size, void **p, unsigned long caller)
{
	size_t i;

	for (i = 0; i < size; i++)
		p[i] = cache_alloc_debugcheck_after(s, flags, p[i], caller);
}
