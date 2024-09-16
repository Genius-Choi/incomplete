void dump_cache(struct cache *cache)
{
	pthread_mutex_lock(&cache->mutex);

	printf("Max buffers %d, Current size %d, Used %d,  %s\n",
		cache->max_buffers, cache->count, cache->used,
		cache->free_list ?  "Free buffers" : "No free buffers");

	pthread_mutex_unlock(&cache->mutex);
}
