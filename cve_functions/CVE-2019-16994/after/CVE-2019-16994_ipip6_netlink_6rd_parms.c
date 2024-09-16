static bool ipip6_netlink_6rd_parms(struct nlattr *data[],
				    struct ip_tunnel_6rd *ip6rd)
{
	bool ret = false;
	memset(ip6rd, 0, sizeof(*ip6rd));

	if (!data)
		return ret;

	if (data[IFLA_IPTUN_6RD_PREFIX]) {
		ret = true;
		ip6rd->prefix = nla_get_in6_addr(data[IFLA_IPTUN_6RD_PREFIX]);
	}

	if (data[IFLA_IPTUN_6RD_RELAY_PREFIX]) {
		ret = true;
		ip6rd->relay_prefix =
			nla_get_be32(data[IFLA_IPTUN_6RD_RELAY_PREFIX]);
	}

	if (data[IFLA_IPTUN_6RD_PREFIXLEN]) {
		ret = true;
		ip6rd->prefixlen = nla_get_u16(data[IFLA_IPTUN_6RD_PREFIXLEN]);
	}

	if (data[IFLA_IPTUN_6RD_RELAY_PREFIXLEN]) {
		ret = true;
		ip6rd->relay_prefixlen =
			nla_get_u16(data[IFLA_IPTUN_6RD_RELAY_PREFIXLEN]);
	}

	return ret;
}
