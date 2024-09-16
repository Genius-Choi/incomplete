static int pegasus_close(struct net_device *net)
{
	pegasus_t *pegasus = netdev_priv(net);

	netif_stop_queue(net);
	if (!(pegasus->flags & PEGASUS_UNPLUG))
		disable_net_traffic(pegasus);
	tasklet_kill(&pegasus->rx_tl);
	unlink_all_urbs(pegasus);

	return 0;
}
