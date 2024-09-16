check_buffer(struct magic_set *ms, struct magic_map *map, const char *dbname)
{
	uint32_t *ptr;
	uint32_t entries, nentries;
	uint32_t version;
	int i, needsbyteswap;

	ptr = CAST(uint32_t *, map->p);
	if (*ptr != MAGICNO) {
		if (swap4(*ptr) != MAGICNO) {
			file_error(ms, 0, "bad magic in `%s'", dbname);
			return -1;
		}
		needsbyteswap = 1;
	} else
		needsbyteswap = 0;
	if (needsbyteswap)
		version = swap4(ptr[1]);
	else
		version = ptr[1];
	if (version != VERSIONNO) {
		file_error(ms, 0, "File %s supports only version %d magic "
		    "files. `%s' is version %d", VERSION,
		    VERSIONNO, dbname, version);
		return -1;
	}
	entries = (uint32_t)(map->len / sizeof(struct magic));
	if ((entries * sizeof(struct magic)) != map->len) {
		file_error(ms, 0, "Size of `%s' %" SIZE_T_FORMAT "u is not "
		    "a multiple of %" SIZE_T_FORMAT "u",
		    dbname, map->len, sizeof(struct magic));
		return -1;
	}
	map->magic[0] = CAST(struct magic *, map->p) + 1;
	nentries = 0;
	for (i = 0; i < MAGIC_SETS; i++) {
		if (needsbyteswap)
			map->nmagic[i] = swap4(ptr[i + 2]);
		else
			map->nmagic[i] = ptr[i + 2];
		if (i != MAGIC_SETS - 1)
			map->magic[i + 1] = map->magic[i] + map->nmagic[i];
		nentries += map->nmagic[i];
	}
	if (entries != nentries + 1) {
		file_error(ms, 0, "Inconsistent entries in `%s' %u != %u",
		    dbname, entries, nentries + 1);
		return -1;
	}
	if (needsbyteswap)
		for (i = 0; i < MAGIC_SETS; i++)
			byteswap(map->magic[i], map->nmagic[i]);
	return 0;
}
