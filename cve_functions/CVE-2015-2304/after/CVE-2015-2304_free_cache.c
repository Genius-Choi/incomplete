free_cache(struct name_cache *cache)
{
	size_t i;

	if (cache != NULL) {
		for (i = 0; i < cache->size; i++)
			free(cache->cache[i].name);
		free(cache);
	}
}
