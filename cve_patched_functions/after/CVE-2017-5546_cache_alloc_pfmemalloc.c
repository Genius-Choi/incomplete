static noinline void *cache_alloc_pfmemalloc(struct kmem_cache *cachep,
				struct kmem_cache_node *n, gfp_t flags)
{
	struct page *page;
	void *obj;
	void *list = NULL;

	if (!gfp_pfmemalloc_allowed(flags))
		return NULL;

	spin_lock(&n->list_lock);
	page = get_first_slab(n, true);
	if (!page) {
		spin_unlock(&n->list_lock);
		return NULL;
	}

	obj = slab_get_obj(cachep, page);
	n->free_objects--;

	fixup_slab_list(cachep, n, page, &list);

	spin_unlock(&n->list_lock);
	fixup_objfreelist_debug(cachep, &list);

	return obj;
}
