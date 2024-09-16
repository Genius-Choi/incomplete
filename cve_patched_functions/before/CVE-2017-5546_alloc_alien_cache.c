static struct alien_cache **alloc_alien_cache(int node, int limit, gfp_t gfp)
{
	struct alien_cache **alc_ptr;
	size_t memsize = sizeof(void *) * nr_node_ids;
	int i;

	if (limit > 1)
		limit = 12;
	alc_ptr = kzalloc_node(memsize, gfp, node);
	if (!alc_ptr)
		return NULL;

	for_each_node(i) {
		if (i == node || !node_online(i))
			continue;
		alc_ptr[i] = __alloc_alien_cache(node, limit, 0xbaadf00d, gfp);
		if (!alc_ptr[i]) {
			for (i--; i >= 0; i--)
				kfree(alc_ptr[i]);
			kfree(alc_ptr);
			return NULL;
		}
	}
	return alc_ptr;
}
