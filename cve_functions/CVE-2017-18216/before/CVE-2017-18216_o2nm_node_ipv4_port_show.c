static ssize_t o2nm_node_ipv4_port_show(struct config_item *item, char *page)
{
	return sprintf(page, "%u\n", ntohs(to_o2nm_node(item)->nd_ipv4_port));
}
