void *kmem_cache_alloc_node_trace(struct kmem_cache *cachep,
				  gfp_t flags,
				  int nodeid,
				  size_t size)
{
	void *ret;

	ret = slab_alloc_node(cachep, flags, nodeid, _RET_IP_);

	kasan_kmalloc(cachep, ret, size, flags);
	trace_kmalloc_node(_RET_IP_, ret,
			   size, cachep->size,
			   flags, nodeid);
	return ret;
}
