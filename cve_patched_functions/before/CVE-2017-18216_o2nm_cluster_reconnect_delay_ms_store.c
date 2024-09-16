static ssize_t o2nm_cluster_reconnect_delay_ms_store(
	struct config_item *item, const char *page, size_t count)
{
	return o2nm_cluster_attr_write(page, count,
                               &to_o2nm_cluster(item)->cl_reconnect_delay_ms);
}
