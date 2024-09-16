apprentice_unmap(struct magic_map *map)
{
	if (map == NULL)
		return;
	if (map->p != NULL) {
#ifdef QUICK
		if (map->len)
			(void)munmap(map->p, map->len);
		else
#endif
		free(map->p);
	} else {
		uint32_t j;
		for (j = 0; j < MAGIC_SETS; j++)
			free(map->magic[j]);
	}
	free(map);
}
