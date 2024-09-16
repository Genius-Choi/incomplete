int __kmem_cache_shrink(struct kmem_cache *cachep)
{
	int ret = 0;
	int node;
	struct kmem_cache_node *n;

	drain_cpu_caches(cachep);

	check_irq_on();
	for_each_kmem_cache_node(cachep, node, n) {
		drain_freelist(cachep, n, INT_MAX);

		ret += !list_empty(&n->slabs_full) ||
			!list_empty(&n->slabs_partial);
	}
	return (ret ? 1 : 0);
}
