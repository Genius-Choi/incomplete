unsigned int inet_addr_type(struct net *net, __be32 addr)
{
	return __inet_dev_addr_type(net, NULL, addr, RT_TABLE_LOCAL);
}
