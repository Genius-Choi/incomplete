__do_kmalloc_node(size_t size, gfp_t flags, int node, unsigned long caller)
{
	struct kmem_cache *cachep;
	void *ret;

	cachep = kmalloc_slab(size, flags);
	if (unlikely(ZERO_OR_NULL_PTR(cachep)))
		return cachep;
	ret = kmem_cache_alloc_node_trace(cachep, flags, node, size);
	kasan_kmalloc(cachep, ret, size, flags);

	return ret;
}
