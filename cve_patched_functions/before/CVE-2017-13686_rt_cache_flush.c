void rt_cache_flush(struct net *net)
{
	rt_genid_bump_ipv4(net);
}
