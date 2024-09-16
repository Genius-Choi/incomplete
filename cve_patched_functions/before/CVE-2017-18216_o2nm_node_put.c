void o2nm_node_put(struct o2nm_node *node)
{
	config_item_put(&node->nd_item);
}
