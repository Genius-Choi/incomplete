static void drain_cpu_caches(struct kmem_cache *cachep)
{
	struct kmem_cache_node *n;
	int node;
	LIST_HEAD(list);

	on_each_cpu(do_drain, cachep, 1);
	check_irq_on();
	for_each_kmem_cache_node(cachep, node, n)
		if (n->alien)
			drain_alien_cache(cachep, n->alien);

	for_each_kmem_cache_node(cachep, node, n) {
		spin_lock_irq(&n->list_lock);
		drain_array_locked(cachep, n->shared, node, true, &list);
		spin_unlock_irq(&n->list_lock);

		slabs_destroy(cachep, &list);
	}
}
