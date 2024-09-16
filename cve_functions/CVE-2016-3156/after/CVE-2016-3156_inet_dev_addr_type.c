unsigned int inet_dev_addr_type(struct net *net, const struct net_device *dev,
				__be32 addr)
{
	u32 rt_table = l3mdev_fib_table(dev) ? : RT_TABLE_LOCAL;

	return __inet_dev_addr_type(net, dev, addr, rt_table);
}
