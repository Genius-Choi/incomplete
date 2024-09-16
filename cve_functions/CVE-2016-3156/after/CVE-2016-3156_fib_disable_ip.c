static void fib_disable_ip(struct net_device *dev, unsigned long event,
			   bool force)
{
	if (fib_sync_down_dev(dev, event, force))
		fib_flush(dev_net(dev));
	rt_cache_flush(dev_net(dev));
	arp_ifdown(dev);
}
