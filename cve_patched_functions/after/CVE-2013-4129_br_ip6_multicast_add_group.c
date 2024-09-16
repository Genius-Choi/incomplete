static int br_ip6_multicast_add_group(struct net_bridge *br,
				      struct net_bridge_port *port,
				      const struct in6_addr *group,
				      __u16 vid)
{
	struct br_ip br_group;

	if (!ipv6_is_transient_multicast(group))
		return 0;

	br_group.u.ip6 = *group;
	br_group.proto = htons(ETH_P_IPV6);
	br_group.vid = vid;

	return br_multicast_add_group(br, port, &br_group);
}
