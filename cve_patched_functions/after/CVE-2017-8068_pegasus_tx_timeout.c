static void pegasus_tx_timeout(struct net_device *net)
{
	pegasus_t *pegasus = netdev_priv(net);
	netif_warn(pegasus, timer, net, "tx timeout\n");
	usb_unlink_urb(pegasus->tx_urb);
	pegasus->stats.tx_errors++;
}
