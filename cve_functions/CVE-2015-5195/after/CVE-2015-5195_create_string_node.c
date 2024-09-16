create_string_node(
	char *str
	)
{
	string_node *sn;
	
	sn = emalloc_zero(sizeof(*sn));
	sn->s = str;

	return sn;
}
