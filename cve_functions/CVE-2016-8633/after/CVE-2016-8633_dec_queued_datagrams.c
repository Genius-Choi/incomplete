static void dec_queued_datagrams(struct fwnet_device *dev)
{
	if (--dev->queued_datagrams == FWNET_MIN_QUEUED_DATAGRAMS)
		netif_wake_queue(dev->netdev);
}
