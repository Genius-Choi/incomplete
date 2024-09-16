static inline void set_store_user_clean(struct kmem_cache *cachep)
{
	atomic_set(&cachep->store_user_clean, 1);
}
