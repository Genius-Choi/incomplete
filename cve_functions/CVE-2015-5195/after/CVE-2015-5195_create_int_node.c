create_int_node(
	int val
	)
{
	int_node *i_n;
	
	i_n = emalloc_zero(sizeof(*i_n));
	i_n->i = val;

	return i_n;
}
