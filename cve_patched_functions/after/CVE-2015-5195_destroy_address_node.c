destroy_address_node(
	address_node *my_node
	)
{
	if (NULL == my_node)
		return;
	NTP_REQUIRE(NULL != my_node->address);

	free(my_node->address);
	free(my_node);
}
