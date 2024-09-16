apprentice_buf(struct magic_set *ms, struct magic *buf, size_t len)
{
	struct magic_map *map;

	if ((map = CAST(struct magic_map *, calloc(1, sizeof(*map)))) == NULL) {
		file_oomem(ms, sizeof(*map));
		return NULL;
	}
	map->len = len;
	map->p = buf;
	map->type = MAP_TYPE_USER;
	if (check_buffer(ms, map, "buffer") != 0) {
		apprentice_unmap(map);
		return NULL;
	}
	return map;
}
