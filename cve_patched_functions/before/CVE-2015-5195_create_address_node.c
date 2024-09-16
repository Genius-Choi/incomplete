create_address_node(
	char *	addr,
	int	type
	)
{
	address_node *my_node;

	NTP_REQUIRE(NULL != addr);
	NTP_REQUIRE(AF_INET == type || 
		    AF_INET6 == type || AF_UNSPEC == type);
	my_node = emalloc_zero(sizeof(*my_node));
	my_node->address = addr;
	my_node->type = (u_short)type;

	return my_node;
}
