int o2nm_configured_node_map(unsigned long *map, unsigned bytes)
{
	struct o2nm_cluster *cluster = o2nm_single_cluster;

	BUG_ON(bytes < (sizeof(cluster->cl_nodes_bitmap)));

	if (cluster == NULL)
		return -EINVAL;

	read_lock(&cluster->cl_nodes_lock);
	memcpy(map, cluster->cl_nodes_bitmap, sizeof(cluster->cl_nodes_bitmap));
	read_unlock(&cluster->cl_nodes_lock);

	return 0;
}
