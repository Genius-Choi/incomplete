unsigned int inet_addr_type_table(struct net *net, __be32 addr, u32 tb_id)
{
	return __inet_dev_addr_type(net, NULL, addr, tb_id);
}
