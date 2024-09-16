static void slabs_destroy(struct kmem_cache *cachep, struct list_head *list)
{
	struct page *page, *n;

	list_for_each_entry_safe(page, n, list, lru) {
		list_del(&page->lru);
		slab_destroy(cachep, page);
	}
}
