unsigned int inet_addr_type_dev_table(struct net *net,
				      const struct net_device *dev,
				      __be32 addr)
{
	u32 rt_table = l3mdev_fib_table(dev) ? : RT_TABLE_LOCAL;

	return __inet_dev_addr_type(net, NULL, addr, rt_table);
}
