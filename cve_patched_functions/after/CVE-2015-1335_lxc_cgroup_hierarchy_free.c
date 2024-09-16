static void lxc_cgroup_hierarchy_free(struct cgroup_hierarchy *h)
{
	if (!h)
		return;
	lxc_free_array((void **)h->subsystems, free);
	free(h->all_mount_points);
	free(h);
}
