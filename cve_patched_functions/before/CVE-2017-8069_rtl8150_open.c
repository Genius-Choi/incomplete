static int rtl8150_open(struct net_device *netdev)
{
	rtl8150_t *dev = netdev_priv(netdev);
	int res;

	if (dev->rx_skb == NULL)
		dev->rx_skb = pull_skb(dev);
	if (!dev->rx_skb)
		return -ENOMEM;

	set_registers(dev, IDR, 6, netdev->dev_addr);

	usb_fill_bulk_urb(dev->rx_urb, dev->udev, usb_rcvbulkpipe(dev->udev, 1),
		      dev->rx_skb->data, RTL8150_MTU, read_bulk_callback, dev);
	if ((res = usb_submit_urb(dev->rx_urb, GFP_KERNEL))) {
		if (res == -ENODEV)
			netif_device_detach(dev->netdev);
		dev_warn(&netdev->dev, "rx_urb submit failed: %d\n", res);
		return res;
	}
	usb_fill_int_urb(dev->intr_urb, dev->udev, usb_rcvintpipe(dev->udev, 3),
		     dev->intr_buff, INTBUFSIZE, intr_callback,
		     dev, dev->intr_interval);
	if ((res = usb_submit_urb(dev->intr_urb, GFP_KERNEL))) {
		if (res == -ENODEV)
			netif_device_detach(dev->netdev);
		dev_warn(&netdev->dev, "intr_urb submit failed: %d\n", res);
		usb_kill_urb(dev->rx_urb);
		return res;
	}
	enable_net_traffic(dev);
	set_carrier(netdev);
	netif_start_queue(netdev);

	return res;
}
