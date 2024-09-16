static int __ath6kl_init_netdev(struct net_device *dev)
{
	int r;

	rtnl_lock();
	r = ar6000_init(dev);
	rtnl_unlock();

	if (r) {
		AR_DEBUG_PRINTF(ATH_DEBUG_ERR,("ar6000_avail: ar6000_init\n"));
		return r;
	}

	return 0;
}
