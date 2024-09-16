static struct cgroup_hierarchy *lxc_cgroup_find_hierarchy(struct cgroup_meta_data *meta_data, const char *subsystem)
{
	size_t i;
	for (i = 0; i <= meta_data->maximum_hierarchy; i++) {
		struct cgroup_hierarchy *h = meta_data->hierarchies[i];
		if (h && lxc_string_in_array(subsystem, (const char **)h->subsystems))
			return h;
	}
	return NULL;
}
