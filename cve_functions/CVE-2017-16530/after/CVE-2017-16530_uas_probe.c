static int uas_probe(struct usb_interface *intf, const struct usb_device_id *id)
{
	int result = -ENOMEM;
	struct Scsi_Host *shost = NULL;
	struct uas_dev_info *devinfo;
	struct usb_device *udev = interface_to_usbdev(intf);
	unsigned long dev_flags;

	if (!uas_use_uas_driver(intf, id, &dev_flags))
		return -ENODEV;

	if (uas_switch_interface(udev, intf))
		return -ENODEV;

	shost = scsi_host_alloc(&uas_host_template,
				sizeof(struct uas_dev_info));
	if (!shost)
		goto set_alt0;

	shost->max_cmd_len = 16 + 252;
	shost->max_id = 1;
	shost->max_lun = 256;
	shost->max_channel = 0;
	shost->sg_tablesize = udev->bus->sg_tablesize;

	devinfo = (struct uas_dev_info *)shost->hostdata;
	devinfo->intf = intf;
	devinfo->udev = udev;
	devinfo->resetting = 0;
	devinfo->shutdown = 0;
	devinfo->flags = dev_flags;
	init_usb_anchor(&devinfo->cmd_urbs);
	init_usb_anchor(&devinfo->sense_urbs);
	init_usb_anchor(&devinfo->data_urbs);
	spin_lock_init(&devinfo->lock);
	INIT_WORK(&devinfo->work, uas_do_work);

	result = uas_configure_endpoints(devinfo);
	if (result)
		goto set_alt0;

	/*
	 * 1 tag is reserved for untagged commands +
	 * 1 tag to avoid off by one errors in some bridge firmwares
	 */
	shost->can_queue = devinfo->qdepth - 2;

	usb_set_intfdata(intf, shost);
	result = scsi_add_host(shost, &intf->dev);
	if (result)
		goto free_streams;

	scsi_scan_host(shost);
	return result;

free_streams:
	uas_free_streams(devinfo);
	usb_set_intfdata(intf, NULL);
set_alt0:
	usb_set_interface(udev, intf->altsetting[0].desc.bInterfaceNumber, 0);
	if (shost)
		scsi_host_put(shost);
	return result;
}
