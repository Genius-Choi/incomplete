int register_netdev(struct net_device *dev)
{
	int err;

	rtnl_lock();
	err = register_netdevice(dev);
	rtnl_unlock();
	return err;
}
