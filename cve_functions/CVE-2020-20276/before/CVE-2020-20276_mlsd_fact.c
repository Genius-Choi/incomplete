void mlsd_fact(char fact, char *buf, size_t len, char *name, char *perms, struct stat *st)
{
	char size[20];

	switch (fact) {
	case 'm':
		strlcat(buf, "modify=", len);
		strlcat(buf, mlsd_time(st->st_mtime), len);
		break;

	case 'p':
		strlcat(buf, "perm=", len);
		strlcat(buf, perms, len);
		break;

	case 't':
		strlcat(buf, "type=", len);
		strlcat(buf, mlsd_type(name, st->st_mode), len);
		break;


	case 's':
		if (S_ISDIR(st->st_mode))
			return;
		snprintf(size, sizeof(size), "size=%" PRIu64, st->st_size);
		strlcat(buf, size, len);
		break;

	default:
		return;
	}

	strlcat(buf, ";", len);
}
