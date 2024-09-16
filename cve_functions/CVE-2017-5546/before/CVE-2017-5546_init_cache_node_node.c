static int init_cache_node_node(int node)
{
	int ret;
	struct kmem_cache *cachep;

	list_for_each_entry(cachep, &slab_caches, list) {
		ret = init_cache_node(cachep, node, GFP_KERNEL);
		if (ret)
			return ret;
	}

	return 0;
}
