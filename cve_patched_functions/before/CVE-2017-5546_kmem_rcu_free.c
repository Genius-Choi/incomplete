static void kmem_rcu_free(struct rcu_head *head)
{
	struct kmem_cache *cachep;
	struct page *page;

	page = container_of(head, struct page, rcu_head);
	cachep = page->slab_cache;

	kmem_freepages(cachep, page);
}
