static struct o2nm_node *to_o2nm_node(struct config_item *item)
{
	return item ? container_of(item, struct o2nm_node, nd_item) : NULL;
}
