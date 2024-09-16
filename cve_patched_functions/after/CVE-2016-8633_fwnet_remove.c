static void fwnet_remove(struct fw_unit *unit)
{
	struct fwnet_peer *peer = dev_get_drvdata(&unit->device);
	struct fwnet_device *dev = peer->dev;
	struct net_device *net;
	int i;

	mutex_lock(&fwnet_device_mutex);

	net = dev->netdev;

	fwnet_remove_peer(peer, dev);

	if (list_empty(&dev->peer_list)) {
		unregister_netdev(net);

		fwnet_fifo_stop(dev);

		for (i = 0; dev->queued_datagrams && i < 5; i++)
			ssleep(1);
		WARN_ON(dev->queued_datagrams);
		list_del(&dev->dev_link);

		free_netdev(net);
	}

	mutex_unlock(&fwnet_device_mutex);
}
