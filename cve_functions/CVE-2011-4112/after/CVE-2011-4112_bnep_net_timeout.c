static void bnep_net_timeout(struct net_device *dev)
{
	BT_DBG("net_timeout");
	netif_wake_queue(dev);
}
