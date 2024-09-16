int hostap_set_word(struct net_device *dev, int rid, u16 val)
{
	struct hostap_interface *iface;
	__le16 tmp = cpu_to_le16(val);
	iface = netdev_priv(dev);
	return iface->local->func->set_rid(dev, rid, &tmp, 2);
}
