static void rtl8150_disconnect(struct usb_interface *intf)
{
	rtl8150_t *dev = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);
	if (dev) {
		set_bit(RTL8150_UNPLUG, &dev->flags);
		tasklet_kill(&dev->tl);
		unregister_netdev(dev->netdev);
		unlink_all_urbs(dev);
		free_all_urbs(dev);
		free_skb_pool(dev);
		if (dev->rx_skb)
			dev_kfree_skb(dev->rx_skb);
		kfree(dev->intr_buff);
		free_netdev(dev->netdev);
	}
}
