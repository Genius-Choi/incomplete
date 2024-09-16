static ssize_t o2nm_cluster_idle_timeout_ms_show(struct config_item *item,
	char *page)
{
	return sprintf(page, "%u\n", to_o2nm_cluster(item)->cl_idle_timeout_ms);
}
