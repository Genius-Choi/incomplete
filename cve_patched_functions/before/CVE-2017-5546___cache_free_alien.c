static int __cache_free_alien(struct kmem_cache *cachep, void *objp,
				int node, int page_node)
{
	struct kmem_cache_node *n;
	struct alien_cache *alien = NULL;
	struct array_cache *ac;
	LIST_HEAD(list);

	n = get_node(cachep, node);
	STATS_INC_NODEFREES(cachep);
	if (n->alien && n->alien[page_node]) {
		alien = n->alien[page_node];
		ac = &alien->ac;
		spin_lock(&alien->lock);
		if (unlikely(ac->avail == ac->limit)) {
			STATS_INC_ACOVERFLOW(cachep);
			__drain_alien_cache(cachep, ac, page_node, &list);
		}
		ac->entry[ac->avail++] = objp;
		spin_unlock(&alien->lock);
		slabs_destroy(cachep, &list);
	} else {
		n = get_node(cachep, page_node);
		spin_lock(&n->list_lock);
		free_block(cachep, &objp, 1, page_node, &list);
		spin_unlock(&n->list_lock);
		slabs_destroy(cachep, &list);
	}
	return 1;
}
