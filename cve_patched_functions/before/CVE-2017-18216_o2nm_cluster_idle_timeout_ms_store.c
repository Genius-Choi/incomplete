static ssize_t o2nm_cluster_idle_timeout_ms_store(struct config_item *item,
	const char *page, size_t count)
{
	struct o2nm_cluster *cluster = to_o2nm_cluster(item);
	ssize_t ret;
	unsigned int val;

	ret =  o2nm_cluster_attr_write(page, count, &val);

	if (ret > 0) {
		if (cluster->cl_idle_timeout_ms != val
			&& o2net_num_connected_peers()) {
			mlog(ML_NOTICE,
			     "o2net: cannot change idle timeout after "
			     "the first peer has agreed to it."
			     "  %d connected peers\n",
			     o2net_num_connected_peers());
			ret = -EINVAL;
		} else if (val <= cluster->cl_keepalive_delay_ms) {
			mlog(ML_NOTICE, "o2net: idle timeout must be larger "
			     "than keepalive delay\n");
			ret = -EINVAL;
		} else {
			cluster->cl_idle_timeout_ms = val;
		}
	}

	return ret;
}
