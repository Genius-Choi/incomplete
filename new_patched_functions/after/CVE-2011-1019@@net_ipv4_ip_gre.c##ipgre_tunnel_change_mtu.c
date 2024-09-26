static int ipgre_tunnel_change_mtu(struct net_device *dev, int new_mtu)
{
	struct ip_tunnel *tunnel = netdev_priv(dev);
	if (new_mtu < 68 ||
	    new_mtu > 0xFFF8 - dev->hard_header_len - tunnel->hlen)
		return -EINVAL;
	dev->mtu = new_mtu;
	return 0;
}
