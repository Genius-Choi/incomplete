static inline unsigned int __inet_dev_addr_type(struct net *net,
						const struct net_device *dev,
						__be32 addr, u32 tb_id)
{
	struct flowi4		fl4 = { .daddr = addr };
	struct fib_result	res;
	unsigned int ret = RTN_BROADCAST;
	struct fib_table *table;

	if (ipv4_is_zeronet(addr) || ipv4_is_lbcast(addr))
		return RTN_BROADCAST;
	if (ipv4_is_multicast(addr))
		return RTN_MULTICAST;

	rcu_read_lock();

	table = fib_get_table(net, tb_id);
	if (table) {
		ret = RTN_UNICAST;
		if (!fib_table_lookup(table, &fl4, &res, FIB_LOOKUP_NOREF)) {
			if (!dev || dev == res.fi->fib_dev)
				ret = res.type;
		}
	}

	rcu_read_unlock();
	return ret;
}
