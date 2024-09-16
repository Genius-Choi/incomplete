create_restrict_node(
	address_node *	addr,
	address_node *	mask,
	int_fifo *	flags,
	int		line_no
	)
{
	restrict_node *my_node;
	
	my_node = emalloc_zero(sizeof(*my_node));
	my_node->addr = addr;
	my_node->mask = mask;
	my_node->flags = flags;
	my_node->line_no = line_no;

	return my_node;
}
