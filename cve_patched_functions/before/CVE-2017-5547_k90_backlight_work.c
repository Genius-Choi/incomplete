static void k90_backlight_work(struct work_struct *work)
{
	int ret;
	struct k90_led *led = container_of(work, struct k90_led, work);
	struct device *dev;
	struct usb_interface *usbif;
	struct usb_device *usbdev;

	if (led->removed)
		return;

	dev = led->cdev.dev->parent;
	usbif = to_usb_interface(dev->parent);
	usbdev = interface_to_usbdev(usbif);

	ret = usb_control_msg(usbdev, usb_sndctrlpipe(usbdev, 0),
			      K90_REQUEST_BRIGHTNESS,
			      USB_DIR_OUT | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, led->brightness, 0,
			      NULL, 0, USB_CTRL_SET_TIMEOUT);
	if (ret != 0)
		dev_warn(dev, "Failed to set backlight brightness (error: %d).\n",
			 ret);
}
