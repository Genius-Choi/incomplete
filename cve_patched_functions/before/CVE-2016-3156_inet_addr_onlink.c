int inet_addr_onlink(struct in_device *in_dev, __be32 a, __be32 b)
{
	rcu_read_lock();
	for_primary_ifa(in_dev) {
		if (inet_ifa_match(a, ifa)) {
			if (!b || inet_ifa_match(b, ifa)) {
				rcu_read_unlock();
				return 1;
			}
		}
	} endfor_ifa(in_dev);
	rcu_read_unlock();
	return 0;
}
