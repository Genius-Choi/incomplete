static void rtl8150_tx_timeout(struct net_device *netdev)
{
	rtl8150_t *dev = netdev_priv(netdev);
	dev_warn(&netdev->dev, "Tx timeout.\n");
	usb_unlink_urb(dev->tx_urb);
	netdev->stats.tx_errors++;
}
