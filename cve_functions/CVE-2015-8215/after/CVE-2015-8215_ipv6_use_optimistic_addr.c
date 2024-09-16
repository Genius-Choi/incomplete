static inline bool ipv6_use_optimistic_addr(struct inet6_dev *idev)
{
#ifdef CONFIG_IPV6_OPTIMISTIC_DAD
	return idev && idev->cnf.optimistic_dad && idev->cnf.use_optimistic;
#else
	return false;
#endif
}
