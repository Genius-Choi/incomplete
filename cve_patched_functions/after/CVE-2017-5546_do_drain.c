static void do_drain(void *arg)
{
	struct kmem_cache *cachep = arg;
	struct array_cache *ac;
	int node = numa_mem_id();
	struct kmem_cache_node *n;
	LIST_HEAD(list);

	check_irq_off();
	ac = cpu_cache_get(cachep);
	n = get_node(cachep, node);
	spin_lock(&n->list_lock);
	free_block(cachep, ac->entry, ac->avail, node, &list);
	spin_unlock(&n->list_lock);
	slabs_destroy(cachep, &list);
	ac->avail = 0;
}
