int lxcfs_mkdir(const char *path, mode_t mode)
{
	if (strncmp(path, "/cgroup", 7) == 0)
		return cg_mkdir(path, mode);

	return -EINVAL;
}
