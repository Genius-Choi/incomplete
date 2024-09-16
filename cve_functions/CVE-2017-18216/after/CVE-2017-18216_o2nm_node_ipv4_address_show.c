static ssize_t o2nm_node_ipv4_address_show(struct config_item *item, char *page)
{
	return sprintf(page, "%pI4\n", &to_o2nm_node(item)->nd_ipv4_address);
}
