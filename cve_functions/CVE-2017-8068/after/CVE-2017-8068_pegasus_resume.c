static int pegasus_resume(struct usb_interface *intf)
{
	struct pegasus *pegasus = usb_get_intfdata(intf);

	netif_device_attach(pegasus->net);
	if (netif_running(pegasus->net)) {
		pegasus->rx_urb->status = 0;
		pegasus->rx_urb->actual_length = 0;
		read_bulk_callback(pegasus->rx_urb);

		pegasus->intr_urb->status = 0;
		pegasus->intr_urb->actual_length = 0;
		intr_callback(pegasus->intr_urb);
	}
	queue_delayed_work(pegasus_workqueue, &pegasus->carrier_check,
				CARRIER_CHECK_DELAY);
	return 0;
}
