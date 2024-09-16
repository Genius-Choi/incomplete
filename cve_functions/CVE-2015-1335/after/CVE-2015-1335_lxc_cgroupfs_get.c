static int lxc_cgroupfs_get(const char *filename, char *value, size_t len, const char *name, const char *lxcpath)
{
	char *subsystem = NULL, *p, *path;
	int ret = -1;

	subsystem = alloca(strlen(filename) + 1);
	strcpy(subsystem, filename);
	if ((p = strchr(subsystem, '.')) != NULL)
		*p = '\0';

	path = lxc_cgroup_get_hierarchy_abs_path(subsystem, name, lxcpath);
	if (path) {
		ret = do_cgroup_get(path, filename, value, len);
		free(path);
	}
	return ret;
}
