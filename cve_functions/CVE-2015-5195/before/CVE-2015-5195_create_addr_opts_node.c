create_addr_opts_node(
	address_node *	addr,
	attr_val_fifo *	options
	)
{
	addr_opts_node *my_node;

	my_node = emalloc_zero(sizeof(*my_node));
	my_node->addr = addr;
	my_node->options = options;

	return my_node;
}
