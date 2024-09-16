void __init ip_static_sysctl_init(void)
{
	register_net_sysctl(&init_net, "net/ipv4/route", ipv4_route_table);
}
