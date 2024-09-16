static ssize_t o2nm_cluster_fence_method_show(
	struct config_item *item, char *page)
{
	struct o2nm_cluster *cluster = to_o2nm_cluster(item);
	ssize_t ret = 0;

	if (cluster)
		ret = sprintf(page, "%s\n",
			      o2nm_fence_method_desc[cluster->cl_fence_method]);
	return ret;
}
