static int alloc_urbs(pegasus_t *pegasus)
{
	int res = -ENOMEM;

	pegasus->rx_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!pegasus->rx_urb) {
		return res;
	}
	pegasus->tx_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!pegasus->tx_urb) {
		usb_free_urb(pegasus->rx_urb);
		return res;
	}
	pegasus->intr_urb = usb_alloc_urb(0, GFP_KERNEL);
	if (!pegasus->intr_urb) {
		usb_free_urb(pegasus->tx_urb);
		usb_free_urb(pegasus->rx_urb);
		return res;
	}

	return 0;
}
