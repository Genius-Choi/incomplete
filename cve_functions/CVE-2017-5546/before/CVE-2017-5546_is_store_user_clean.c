static inline bool is_store_user_clean(struct kmem_cache *cachep)
{
	return atomic_read(&cachep->store_user_clean) == 1;
}
