int ipv6_chk_addr(struct net *net, const struct in6_addr *addr,
		  const struct net_device *dev, int strict)
{
	return ipv6_chk_addr_and_flags(net, addr, dev, strict, IFA_F_TENTATIVE);
}
