static void lxc_cgroup_mount_point_free(struct cgroup_mount_point *mp)
{
	if (!mp)
		return;
	free(mp->mount_point);
	free(mp->mount_prefix);
	free(mp);
}
