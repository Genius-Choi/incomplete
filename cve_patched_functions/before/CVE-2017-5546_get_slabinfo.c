void get_slabinfo(struct kmem_cache *cachep, struct slabinfo *sinfo)
{
	unsigned long active_objs, num_objs, active_slabs;
	unsigned long total_slabs = 0, free_objs = 0, shared_avail = 0;
	unsigned long free_slabs = 0;
	int node;
	struct kmem_cache_node *n;

	for_each_kmem_cache_node(cachep, node, n) {
		check_irq_on();
		spin_lock_irq(&n->list_lock);

		total_slabs += n->total_slabs;
		free_slabs += n->free_slabs;
		free_objs += n->free_objects;

		if (n->shared)
			shared_avail += n->shared->avail;

		spin_unlock_irq(&n->list_lock);
	}
	num_objs = total_slabs * cachep->num;
	active_slabs = total_slabs - free_slabs;
	active_objs = num_objs - free_objs;

	sinfo->active_objs = active_objs;
	sinfo->num_objs = num_objs;
	sinfo->active_slabs = active_slabs;
	sinfo->num_slabs = total_slabs;
	sinfo->shared_avail = shared_avail;
	sinfo->limit = cachep->limit;
	sinfo->batchcount = cachep->batchcount;
	sinfo->shared = cachep->shared;
	sinfo->objects_per_slab = cachep->num;
	sinfo->cache_order = cachep->gfporder;
}
