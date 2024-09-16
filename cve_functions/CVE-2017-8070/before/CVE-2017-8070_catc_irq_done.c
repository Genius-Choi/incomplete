static void catc_irq_done(struct urb *urb)
{
	struct catc *catc = urb->context;
	u8 *data = urb->transfer_buffer;
	int status = urb->status;
	unsigned int hasdata = 0, linksts = LinkNoChange;
	int res;

	if (!catc->is_f5u011) {
		hasdata = data[1] & 0x80;
		if (data[1] & 0x40)
			linksts = LinkGood;
		else if (data[1] & 0x20)
			linksts = LinkBad;
	} else {
		hasdata = (unsigned int)(be16_to_cpup((__be16*)data) & 0x0fff);
		if (data[0] == 0x90)
			linksts = LinkGood;
		else if (data[0] == 0xA0)
			linksts = LinkBad;
	}

	switch (status) {
	case 0:			/* success */
		break;
	case -ECONNRESET:	/* unlink */
	case -ENOENT:
	case -ESHUTDOWN:
		return;
	/* -EPIPE:  should clear the halt */
	default:		/* error */
		dev_dbg(&urb->dev->dev,
			"irq_done, status %d, data %02x %02x.\n",
			status, data[0], data[1]);
		goto resubmit;
	}

	if (linksts == LinkGood) {
		netif_carrier_on(catc->netdev);
		netdev_dbg(catc->netdev, "link ok\n");
	}

	if (linksts == LinkBad) {
		netif_carrier_off(catc->netdev);
		netdev_dbg(catc->netdev, "link bad\n");
	}

	if (hasdata) {
		if (test_and_set_bit(RX_RUNNING, &catc->flags)) {
			if (catc->is_f5u011)
				atomic_inc(&catc->recq_sz);
		} else {
			catc->rx_urb->dev = catc->usbdev;
			if ((res = usb_submit_urb(catc->rx_urb, GFP_ATOMIC)) < 0) {
				dev_err(&catc->usbdev->dev,
					"submit(rx_urb) status %d\n", res);
			}
		} 
	}
resubmit:
	res = usb_submit_urb (urb, GFP_ATOMIC);
	if (res)
		dev_err(&catc->usbdev->dev,
			"can't resubmit intr, %s-%s, status %d\n",
			catc->usbdev->bus->bus_name,
			catc->usbdev->devpath, res);
}
