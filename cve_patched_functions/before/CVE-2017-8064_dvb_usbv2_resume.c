int dvb_usbv2_resume(struct usb_interface *intf)
{
	struct dvb_usb_device *d = usb_get_intfdata(intf);
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	return dvb_usbv2_resume_common(d);
}
