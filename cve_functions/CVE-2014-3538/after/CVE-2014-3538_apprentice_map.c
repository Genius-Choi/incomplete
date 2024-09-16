apprentice_map(struct magic_set *ms, const char *fn)
{
	int fd;
	struct stat st;
	uint32_t *ptr;
	uint32_t version, entries, nentries;
	int needsbyteswap;
	char *dbname = NULL;
	struct magic_map *map;
	size_t i;

	fd = -1;
	if ((map = CAST(struct magic_map *, calloc(1, sizeof(*map)))) == NULL) {
		file_oomem(ms, sizeof(*map));
		goto error;
	}

	dbname = mkdbname(ms, fn, 0);
	if (dbname == NULL)
		goto error;

	if ((fd = open(dbname, O_RDONLY|O_BINARY)) == -1)
		goto error;

	if (fstat(fd, &st) == -1) {
		file_error(ms, errno, "cannot stat `%s'", dbname);
		goto error;
	}
	if (st.st_size < 8 || st.st_size > MAXMAGIC_SIZE) {
		file_error(ms, 0, "file `%s' is too %s", dbname,
		    st.st_size < 8 ? "small" : "large");
		goto error;
	}

	map->len = (size_t)st.st_size;
#ifdef QUICK
	if ((map->p = mmap(0, (size_t)st.st_size, PROT_READ|PROT_WRITE,
	    MAP_PRIVATE|MAP_FILE, fd, (off_t)0)) == MAP_FAILED) {
		file_error(ms, errno, "cannot map `%s'", dbname);
		goto error;
	}
#else
	if ((map->p = CAST(void *, malloc(map->len))) == NULL) {
		file_oomem(ms, map->len);
		goto error;
	}
	if (read(fd, map->p, map->len) != (ssize_t)map->len) {
		file_badread(ms);
		goto error;
	}
	map->len = 0;
#define RET	1
#endif
	(void)close(fd);
	fd = -1;
	ptr = CAST(uint32_t *, map->p);
	if (*ptr != MAGICNO) {
		if (swap4(*ptr) != MAGICNO) {
			file_error(ms, 0, "bad magic in `%s'", dbname);
			goto error;
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
		goto error;
	}
	entries = (uint32_t)(st.st_size / sizeof(struct magic));
	if ((off_t)(entries * sizeof(struct magic)) != st.st_size) {
		file_error(ms, 0, "Size of `%s' %" INT64_T_FORMAT "u is not "
		    "a multiple of %" SIZE_T_FORMAT "u",
		    dbname, (unsigned long long)st.st_size,
		    sizeof(struct magic));
		goto error;
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
		goto error;
	}
	if (needsbyteswap)
		for (i = 0; i < MAGIC_SETS; i++)
			byteswap(map->magic[i], map->nmagic[i]);
	free(dbname);
	return map;

error:
	if (fd != -1)
		(void)close(fd);
	apprentice_unmap(map);
	free(dbname);
	return NULL;
}
