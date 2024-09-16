static struct cgroup_meta_data *lxc_cgroup_get_meta(struct cgroup_meta_data *meta_data)
{
	meta_data->ref++;
	return meta_data;
}
