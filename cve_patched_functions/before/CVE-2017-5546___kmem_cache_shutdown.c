int __kmem_cache_shutdown(struct kmem_cache *cachep)
{
	return __kmem_cache_shrink(cachep);
}
