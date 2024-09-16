static inline bool slave_dev_support_netpoll(struct net_device *slave_dev)
{
	if (slave_dev->priv_flags & IFF_DISABLE_NETPOLL)
		return false;
	if (!slave_dev->netdev_ops->ndo_poll_controller)
		return false;
	return true;
}
