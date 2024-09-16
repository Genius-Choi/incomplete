void __init taskstats_init_early(void)
{
	unsigned int i;

	taskstats_cache = KMEM_CACHE(taskstats, SLAB_PANIC);
	for_each_possible_cpu(i) {
		INIT_LIST_HEAD(&(per_cpu(listener_array, i).list));
		init_rwsem(&(per_cpu(listener_array, i).sem));
	}
}
