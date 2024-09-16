apprentice_compile(struct magic_set *ms, struct magic_map *map, const char *fn)
{
	static const size_t nm = sizeof(*map->nmagic) * MAGIC_SETS;
	static const size_t m = sizeof(**map->magic);
	int fd = -1;
	size_t len;
	char *dbname;
	int rv = -1;
	uint32_t i;
	union {
		struct magic m;
		uint32_t h[2 + MAGIC_SETS];
	} hdr;

	dbname = mkdbname(ms, fn, 1);

	if (dbname == NULL) 
		goto out;

	if ((fd = open(dbname, O_WRONLY|O_CREAT|O_TRUNC|O_BINARY, 0644)) == -1) 
	{
		file_error(ms, errno, "cannot open `%s'", dbname);
		goto out;
	}
	memset(&hdr, 0, sizeof(hdr));
	hdr.h[0] = MAGICNO;
	hdr.h[1] = VERSIONNO;
	memcpy(hdr.h + 2, map->nmagic, nm);

	if (write(fd, &hdr, sizeof(hdr)) != (ssize_t)sizeof(hdr)) {
		file_error(ms, errno, "error writing `%s'", dbname);
		goto out;
	}

	for (i = 0; i < MAGIC_SETS; i++) {
		len = m * map->nmagic[i];
		if (write(fd, map->magic[i], len) != (ssize_t)len) {
			file_error(ms, errno, "error writing `%s'", dbname);
			goto out;
		}
	}

	if (fd != -1)
		(void)close(fd);
	rv = 0;
out:
	free(dbname);
	return rv;
}
