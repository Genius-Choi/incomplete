static int lxc_cgroup_set_data(const char *filename, const char *value, struct cgfs_data *d)
{
	char *subsystem = NULL, *p, *path;
	int ret = -1;

	subsystem = alloca(strlen(filename) + 1);
	strcpy(subsystem, filename);
	if ((p = strchr(subsystem, '.')) != NULL)
		*p = '\0';

	path = lxc_cgroup_get_hierarchy_abs_path_data(subsystem, d);
	if (path) {
		ret = do_cgroup_set(path, filename, value);
		free(path);
	}
	return ret;
}
