apprentice_map(struct magic_set *ms, const char *fn)
{
	int fd;
	struct stat st;
	char *dbname = NULL;
	struct magic_map *map;

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
	map->type = MAP_TYPE_MMAP;
#else
	if ((map->p = CAST(void *, malloc(map->len))) == NULL) {
		file_oomem(ms, map->len);
		goto error;
	}
	if (read(fd, map->p, map->len) != (ssize_t)map->len) {
		file_badread(ms);
		goto error;
	}
	map->type = MAP_TYPE_MALLOC;
#define RET	1
#endif
	(void)close(fd);
	fd = -1;

	if (check_buffer(ms, map, dbname) != 0)
		goto error;

	free(dbname);
	return map;

error:
	if (fd != -1)
		(void)close(fd);
	apprentice_unmap(map);
	free(dbname);
	return NULL;
}
