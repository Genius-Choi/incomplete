static int fwnet_change_mtu(struct net_device *net, int new_mtu)
{
	if (new_mtu < 68)
		return -EINVAL;

	net->mtu = new_mtu;
	return 0;
}
