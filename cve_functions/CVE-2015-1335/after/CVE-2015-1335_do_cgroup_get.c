static int do_cgroup_get(const char *cgroup_path, const char *sub_filename,
			 char *value, size_t len)
{
	const char *parts[3] = {
		cgroup_path,
		sub_filename,
		NULL
	};
	char *filename;
	int ret, saved_errno;

	filename = lxc_string_join("/", parts, false);
	if (!filename)
		return -1;

	ret = lxc_read_from_file(filename, value, len);
	saved_errno = errno;
	free(filename);
	errno = saved_errno;
	return ret;
}
