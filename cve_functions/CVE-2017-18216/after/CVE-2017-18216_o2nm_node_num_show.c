static ssize_t o2nm_node_num_show(struct config_item *item, char *page)
{
	return sprintf(page, "%d\n", to_o2nm_node(item)->nd_num);
}
