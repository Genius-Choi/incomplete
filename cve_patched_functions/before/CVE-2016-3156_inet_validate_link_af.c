static int inet_validate_link_af(const struct net_device *dev,
				 const struct nlattr *nla)
{
	struct nlattr *a, *tb[IFLA_INET_MAX+1];
	int err, rem;

	if (dev && !__in_dev_get_rtnl(dev))
		return -EAFNOSUPPORT;

	err = nla_parse_nested(tb, IFLA_INET_MAX, nla, inet_af_policy);
	if (err < 0)
		return err;

	if (tb[IFLA_INET_CONF]) {
		nla_for_each_nested(a, tb[IFLA_INET_CONF], rem) {
			int cfgid = nla_type(a);

			if (nla_len(a) < 4)
				return -EINVAL;

			if (cfgid <= 0 || cfgid > IPV4_DEVCONF_MAX)
				return -EINVAL;
		}
	}

	return 0;
}
