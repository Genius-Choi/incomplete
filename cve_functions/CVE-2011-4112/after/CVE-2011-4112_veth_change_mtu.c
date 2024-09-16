static int veth_change_mtu(struct net_device *dev, int new_mtu)
{
	if (!is_valid_veth_mtu(new_mtu))
		return -EINVAL;
	dev->mtu = new_mtu;
	return 0;
}
