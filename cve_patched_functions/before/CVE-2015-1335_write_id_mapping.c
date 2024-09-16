static int write_id_mapping(enum idtype idtype, pid_t pid, const char *buf,
			    size_t buf_size)
{
	char path[PATH_MAX];
	int ret, closeret;
	FILE *f;

	ret = snprintf(path, PATH_MAX, "/proc/%d/%cid_map", pid, idtype == ID_TYPE_UID ? 'u' : 'g');
	if (ret < 0 || ret >= PATH_MAX) {
		fprintf(stderr, "%s: path name too long\n", __func__);
		return -E2BIG;
	}
	f = fopen(path, "w");
	if (!f) {
		perror("open");
		return -EINVAL;
	}
	ret = fwrite(buf, buf_size, 1, f);
	if (ret < 0)
		SYSERROR("writing id mapping");
	closeret = fclose(f);
	if (closeret)
		SYSERROR("writing id mapping");
	return ret < 0 ? ret : closeret;
}
