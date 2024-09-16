u8 o2nm_this_node(void)
{
	u8 node_num = O2NM_MAX_NODES;

	if (o2nm_single_cluster && o2nm_single_cluster->cl_has_local)
		node_num = o2nm_single_cluster->cl_local_node;

	return node_num;
}
