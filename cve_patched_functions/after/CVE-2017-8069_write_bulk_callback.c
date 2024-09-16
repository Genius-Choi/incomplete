static void write_bulk_callback(struct urb *urb)
{
	rtl8150_t *dev;
	int status = urb->status;

	dev = urb->context;
	if (!dev)
		return;
	dev_kfree_skb_irq(dev->tx_skb);
	if (!netif_device_present(dev->netdev))
		return;
	if (status)
		dev_info(&urb->dev->dev, "%s: Tx status %d\n",
			 dev->netdev->name, status);
	netif_trans_update(dev->netdev);
	netif_wake_queue(dev->netdev);
}
