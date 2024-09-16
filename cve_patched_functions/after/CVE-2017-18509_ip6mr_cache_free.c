static inline void ip6mr_cache_free(struct mfc6_cache *c)
{
	kmem_cache_free(mrt_cachep, c);
}
