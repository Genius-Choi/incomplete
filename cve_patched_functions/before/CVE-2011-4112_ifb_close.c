static int ifb_close(struct net_device *dev)
{
	struct ifb_private *dp = netdev_priv(dev);

	tasklet_kill(&dp->ifb_tasklet);
	netif_stop_queue(dev);
	__skb_queue_purge(&dp->rq);
	__skb_queue_purge(&dp->tq);
	return 0;
}
