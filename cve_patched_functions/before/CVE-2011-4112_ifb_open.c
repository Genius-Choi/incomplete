static int ifb_open(struct net_device *dev)
{
	struct ifb_private *dp = netdev_priv(dev);

	tasklet_init(&dp->ifb_tasklet, ri_tasklet, (unsigned long)dev);
	__skb_queue_head_init(&dp->rq);
	__skb_queue_head_init(&dp->tq);
	netif_start_queue(dev);

	return 0;
}
