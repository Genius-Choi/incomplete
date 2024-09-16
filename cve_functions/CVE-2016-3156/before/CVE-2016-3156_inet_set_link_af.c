static int inet_set_link_af(struct net_device *dev, const struct nlattr *nla)
{
	struct in_device *in_dev = __in_dev_get_rtnl(dev);
	struct nlattr *a, *tb[IFLA_INET_MAX+1];
	int rem;

	if (!in_dev)
		return -EAFNOSUPPORT;

	if (nla_parse_nested(tb, IFLA_INET_MAX, nla, NULL) < 0)
		BUG();

	if (tb[IFLA_INET_CONF]) {
		nla_for_each_nested(a, tb[IFLA_INET_CONF], rem)
			ipv4_devconf_set(in_dev, nla_type(a), nla_get_u32(a));
	}

	return 0;
}
