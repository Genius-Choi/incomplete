static inline struct page *alloc_slab_page(gfp_t flags, int node,
					struct kmem_cache_order_objects oo)
{
	int order = oo_order(oo);

	if (node == -1)
		return alloc_pages(flags, order);
	else
		return alloc_pages_node(node, flags, order);
}
