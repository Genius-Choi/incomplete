static void cache_grow_end(struct kmem_cache *cachep, struct page *page)
{
	struct kmem_cache_node *n;
	void *list = NULL;

	check_irq_off();

	if (!page)
		return;

	INIT_LIST_HEAD(&page->lru);
	n = get_node(cachep, page_to_nid(page));

	spin_lock(&n->list_lock);
	n->total_slabs++;
	if (!page->active) {
		list_add_tail(&page->lru, &(n->slabs_free));
		n->free_slabs++;
	} else
		fixup_slab_list(cachep, n, page, &list);

	STATS_INC_GROWN(cachep);
	n->free_objects += cachep->num - page->active;
	spin_unlock(&n->list_lock);

	fixup_objfreelist_debug(cachep, &list);
}
