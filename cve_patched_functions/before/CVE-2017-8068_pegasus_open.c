static int pegasus_open(struct net_device *net)
{
	pegasus_t *pegasus = netdev_priv(net);
	int res=-ENOMEM;

	if (pegasus->rx_skb == NULL)
		pegasus->rx_skb = __netdev_alloc_skb_ip_align(pegasus->net,
							      PEGASUS_MTU,
							      GFP_KERNEL);
	if (!pegasus->rx_skb)
		goto exit;

	res = set_registers(pegasus, EthID, 6, net->dev_addr);

	usb_fill_bulk_urb(pegasus->rx_urb, pegasus->usb,
			  usb_rcvbulkpipe(pegasus->usb, 1),
			  pegasus->rx_skb->data, PEGASUS_MTU,
			  read_bulk_callback, pegasus);
	if ((res = usb_submit_urb(pegasus->rx_urb, GFP_KERNEL))) {
		if (res == -ENODEV)
			netif_device_detach(pegasus->net);
		netif_dbg(pegasus, ifup, net, "failed rx_urb, %d\n", res);
		goto exit;
	}

	usb_fill_int_urb(pegasus->intr_urb, pegasus->usb,
			 usb_rcvintpipe(pegasus->usb, 3),
			 pegasus->intr_buff, sizeof(pegasus->intr_buff),
			 intr_callback, pegasus, pegasus->intr_interval);
	if ((res = usb_submit_urb(pegasus->intr_urb, GFP_KERNEL))) {
		if (res == -ENODEV)
			netif_device_detach(pegasus->net);
		netif_dbg(pegasus, ifup, net, "failed intr_urb, %d\n", res);
		usb_kill_urb(pegasus->rx_urb);
		goto exit;
	}
	res = enable_net_traffic(net, pegasus->usb);
	if (res < 0) {
		netif_dbg(pegasus, ifup, net,
			  "can't enable_net_traffic() - %d\n", res);
		res = -EIO;
		usb_kill_urb(pegasus->rx_urb);
		usb_kill_urb(pegasus->intr_urb);
		goto exit;
	}
	set_carrier(net);
	netif_start_queue(net);
	netif_dbg(pegasus, ifup, net, "open\n");
	res = 0;
exit:
	return res;
}
