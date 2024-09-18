static int do_cgroup_set(const char *cgroup_path, const char *sub_filename,
			 const char *value)
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

	ret = lxc_write_to_file(filename, value, strlen(value), false);
	saved_errno = errno;
	free(filename);
	errno = saved_errno;
	return ret;
}
