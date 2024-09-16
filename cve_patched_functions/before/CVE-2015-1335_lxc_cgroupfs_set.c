static int lxc_cgroupfs_set(const char *filename, const char *value, const char *name, const char *lxcpath)
{
	char *subsystem = NULL, *p, *path;
	int ret = -1;

	subsystem = alloca(strlen(filename) + 1);
	strcpy(subsystem, filename);
	if ((p = strchr(subsystem, '.')) != NULL)
		*p = '\0';

	path = lxc_cgroup_get_hierarchy_abs_path(subsystem, name, lxcpath);
	if (path) {
		ret = do_cgroup_set(path, filename, value);
		free(path);
	}
	return ret;
}
