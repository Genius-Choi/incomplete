static struct xps_map *remove_xps_queue(struct xps_dev_maps *dev_maps,
					int cpu, u16 index)
{
	struct xps_map *map = NULL;
	int pos;

	if (dev_maps)
		map = xmap_dereference(dev_maps->cpu_map[cpu]);

	for (pos = 0; map && pos < map->len; pos++) {
		if (map->queues[pos] == index) {
			if (map->len > 1) {
				map->queues[pos] = map->queues[--map->len];
			} else {
				RCU_INIT_POINTER(dev_maps->cpu_map[cpu], NULL);
				kfree_rcu(map, rcu);
				map = NULL;
			}
			break;
		}
	}

	return map;
}
