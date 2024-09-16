static void o2nm_node_release(struct config_item *item)
{
	struct o2nm_node *node = to_o2nm_node(item);
	kfree(node);
}
