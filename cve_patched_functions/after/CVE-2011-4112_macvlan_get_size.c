static size_t macvlan_get_size(const struct net_device *dev)
{
	return nla_total_size(4);
}
