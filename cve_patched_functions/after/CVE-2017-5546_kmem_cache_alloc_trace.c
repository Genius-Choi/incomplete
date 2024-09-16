kmem_cache_alloc_trace(struct kmem_cache *cachep, gfp_t flags, size_t size)
{
	void *ret;

	ret = slab_alloc(cachep, flags, _RET_IP_);

	kasan_kmalloc(cachep, ret, size, flags);
	trace_kmalloc(_RET_IP_, ret,
		      size, cachep->size, flags);
	return ret;
}
