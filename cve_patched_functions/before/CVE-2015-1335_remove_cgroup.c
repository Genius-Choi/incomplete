static int remove_cgroup(struct cgroup_mount_point *mp,
			 const char *path, bool recurse)
{
	return create_or_remove_cgroup(true, mp, path, recurse);
}
