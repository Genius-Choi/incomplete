static int rtl8150_resume(struct usb_interface *intf)
{
	rtl8150_t *dev = usb_get_intfdata(intf);

	netif_device_attach(dev->netdev);
	if (netif_running(dev->netdev)) {
		dev->rx_urb->status = 0;
		dev->rx_urb->actual_length = 0;
		read_bulk_callback(dev->rx_urb);

		dev->intr_urb->status = 0;
		dev->intr_urb->actual_length = 0;
		intr_callback(dev->intr_urb);
	}
	return 0;
}
