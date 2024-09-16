static noinline void cache_free_pfmemalloc(struct kmem_cache *cachep,
					struct page *page, void *objp)
{
	struct kmem_cache_node *n;
	int page_node;
	LIST_HEAD(list);

	page_node = page_to_nid(page);
	n = get_node(cachep, page_node);

	spin_lock(&n->list_lock);
	free_block(cachep, &objp, 1, page_node, &list);
	spin_unlock(&n->list_lock);

	slabs_destroy(cachep, &list);
}
