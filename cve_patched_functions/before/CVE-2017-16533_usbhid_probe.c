static int usbhid_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	struct usb_host_interface *interface = intf->cur_altsetting;
	struct usb_device *dev = interface_to_usbdev(intf);
	struct usbhid_device *usbhid;
	struct hid_device *hid;
	unsigned int n, has_in = 0;
	size_t len;
	int ret;

	dbg_hid("HID probe called for ifnum %d\n",
			intf->altsetting->desc.bInterfaceNumber);

	for (n = 0; n < interface->desc.bNumEndpoints; n++)
		if (usb_endpoint_is_int_in(&interface->endpoint[n].desc))
			has_in++;
	if (!has_in) {
		hid_err(intf, "couldn't find an input interrupt endpoint\n");
		return -ENODEV;
	}

	hid = hid_allocate_device();
	if (IS_ERR(hid))
		return PTR_ERR(hid);

	usb_set_intfdata(intf, hid);
	hid->ll_driver = &usb_hid_driver;
	hid->ff_init = hid_pidff_init;
#ifdef CONFIG_USB_HIDDEV
	hid->hiddev_connect = hiddev_connect;
	hid->hiddev_disconnect = hiddev_disconnect;
	hid->hiddev_hid_event = hiddev_hid_event;
	hid->hiddev_report_event = hiddev_report_event;
#endif
	hid->dev.parent = &intf->dev;
	hid->bus = BUS_USB;
	hid->vendor = le16_to_cpu(dev->descriptor.idVendor);
	hid->product = le16_to_cpu(dev->descriptor.idProduct);
	hid->name[0] = 0;
	hid->quirks = usbhid_lookup_quirk(hid->vendor, hid->product);
	if (intf->cur_altsetting->desc.bInterfaceProtocol ==
			USB_INTERFACE_PROTOCOL_MOUSE)
		hid->type = HID_TYPE_USBMOUSE;
	else if (intf->cur_altsetting->desc.bInterfaceProtocol == 0)
		hid->type = HID_TYPE_USBNONE;

	if (dev->manufacturer)
		strlcpy(hid->name, dev->manufacturer, sizeof(hid->name));

	if (dev->product) {
		if (dev->manufacturer)
			strlcat(hid->name, " ", sizeof(hid->name));
		strlcat(hid->name, dev->product, sizeof(hid->name));
	}

	if (!strlen(hid->name))
		snprintf(hid->name, sizeof(hid->name), "HID %04x:%04x",
			 le16_to_cpu(dev->descriptor.idVendor),
			 le16_to_cpu(dev->descriptor.idProduct));

	usb_make_path(dev, hid->phys, sizeof(hid->phys));
	strlcat(hid->phys, "/input", sizeof(hid->phys));
	len = strlen(hid->phys);
	if (len < sizeof(hid->phys) - 1)
		snprintf(hid->phys + len, sizeof(hid->phys) - len,
			 "%d", intf->altsetting[0].desc.bInterfaceNumber);

	if (usb_string(dev, dev->descriptor.iSerialNumber, hid->uniq, 64) <= 0)
		hid->uniq[0] = 0;

	usbhid = kzalloc(sizeof(*usbhid), GFP_KERNEL);
	if (usbhid == NULL) {
		ret = -ENOMEM;
		goto err;
	}

	hid->driver_data = usbhid;
	usbhid->hid = hid;
	usbhid->intf = intf;
	usbhid->ifnum = interface->desc.bInterfaceNumber;

	init_waitqueue_head(&usbhid->wait);
	INIT_WORK(&usbhid->reset_work, hid_reset);
	setup_timer(&usbhid->io_retry, hid_retry_timeout, (unsigned long) hid);
	spin_lock_init(&usbhid->lock);

	ret = hid_add_device(hid);
	if (ret) {
		if (ret != -ENODEV)
			hid_err(intf, "can't add hid device: %d\n", ret);
		goto err_free;
	}

	return 0;
err_free:
	kfree(usbhid);
err:
	hid_destroy_device(hid);
	return ret;
}
