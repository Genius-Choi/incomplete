static inline int oo_objects(struct kmem_cache_order_objects x)
{
	return x.x & ((1 << 16) - 1);
}
