static void pegasus_disconnect(struct usb_interface *intf)
{
	struct pegasus *pegasus = usb_get_intfdata(intf);

	usb_set_intfdata(intf, NULL);
	if (!pegasus) {
		dev_dbg(&intf->dev, "unregistering non-bound device?\n");
		return;
	}

	pegasus->flags |= PEGASUS_UNPLUG;
	cancel_delayed_work(&pegasus->carrier_check);
	unregister_netdev(pegasus->net);
	unlink_all_urbs(pegasus);
	free_all_urbs(pegasus);
	if (pegasus->rx_skb != NULL) {
		dev_kfree_skb(pegasus->rx_skb);
		pegasus->rx_skb = NULL;
	}
	free_netdev(pegasus->net);
	pegasus_dec_workqueue();
}
