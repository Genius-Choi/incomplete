static void __init set_up_node(struct kmem_cache *cachep, int index)
{
	int node;

	for_each_online_node(node) {
		cachep->node[node] = &init_kmem_cache_node[index + node];
		cachep->node[node]->next_reap = jiffies +
		    REAPTIMEOUT_NODE +
		    ((unsigned long)cachep) % REAPTIMEOUT_NODE;
	}
}
