struct in6_addr *fl6_update_dst(struct flowi6 *fl6,
				const struct ipv6_txoptions *opt,
				struct in6_addr *orig)
{
	if (!opt || !opt->srcrt)
		return NULL;

	*orig = fl6->daddr;
	fl6->daddr = *((struct rt0_hdr *)opt->srcrt)->addr;
	return orig;
}
