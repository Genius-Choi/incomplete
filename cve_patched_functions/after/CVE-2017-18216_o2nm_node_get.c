void o2nm_node_get(struct o2nm_node *node)
{
	config_item_get(&node->nd_item);
}
