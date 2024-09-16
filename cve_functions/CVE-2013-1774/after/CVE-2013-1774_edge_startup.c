static int edge_startup(struct usb_serial *serial)
{
	struct edgeport_serial *edge_serial;
	int status;

	/* create our private serial structure */
	edge_serial = kzalloc(sizeof(struct edgeport_serial), GFP_KERNEL);
	if (edge_serial == NULL) {
		dev_err(&serial->dev->dev, "%s - Out of memory\n", __func__);
		return -ENOMEM;
	}
	mutex_init(&edge_serial->es_lock);
	edge_serial->serial = serial;
	usb_set_serial_data(serial, edge_serial);

	status = download_fw(edge_serial);
	if (status) {
		kfree(edge_serial);
		return status;
	}

	return 0;
}
