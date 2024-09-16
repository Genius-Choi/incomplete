apprentice_unmap(struct magic_map *map)
{
	if (map == NULL)
		return;

	switch (map->type) {
#ifdef QUICK
	case MAP_TYPE_MMAP:
		if (map->p)
			(void)munmap(map->p, map->len);
		break;
#endif
	case MAP_TYPE_MALLOC:
		free(map->p);
		break;
	case MAP_TYPE_USER:
		break;
	default:
		abort();
	}
	free(map);
}
