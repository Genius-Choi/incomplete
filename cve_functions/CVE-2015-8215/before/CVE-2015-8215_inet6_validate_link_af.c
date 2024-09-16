static int inet6_validate_link_af(const struct net_device *dev,
				  const struct nlattr *nla)
{
	struct nlattr *tb[IFLA_INET6_MAX + 1];

	if (dev && !__in6_dev_get(dev))
		return -EAFNOSUPPORT;

	return nla_parse_nested(tb, IFLA_INET6_MAX, nla, inet6_af_policy);
}
