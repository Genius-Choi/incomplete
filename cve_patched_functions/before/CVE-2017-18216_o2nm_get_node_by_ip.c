struct o2nm_node *o2nm_get_node_by_ip(__be32 addr)
{
	struct o2nm_node *node = NULL;
	struct o2nm_cluster *cluster = o2nm_single_cluster;

	if (cluster == NULL)
		goto out;

	read_lock(&cluster->cl_nodes_lock);
	node = o2nm_node_ip_tree_lookup(cluster, addr, NULL, NULL);
	if (node)
		config_item_get(&node->nd_item);
	read_unlock(&cluster->cl_nodes_lock);

out:
	return node;
}
