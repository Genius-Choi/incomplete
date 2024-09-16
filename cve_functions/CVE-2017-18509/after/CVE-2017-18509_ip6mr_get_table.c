static struct mr6_table *ip6mr_get_table(struct net *net, u32 id)
{
	return net->ipv6.mrt6;
}
