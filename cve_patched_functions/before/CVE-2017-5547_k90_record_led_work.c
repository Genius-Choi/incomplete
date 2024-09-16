static void k90_record_led_work(struct work_struct *work)
{
	int ret;
	struct k90_led *led = container_of(work, struct k90_led, work);
	struct device *dev;
	struct usb_interface *usbif;
	struct usb_device *usbdev;
	int value;

	if (led->removed)
		return;

	dev = led->cdev.dev->parent;
	usbif = to_usb_interface(dev->parent);
	usbdev = interface_to_usbdev(usbif);

	if (led->brightness > 0)
		value = K90_MACRO_LED_ON;
	else
		value = K90_MACRO_LED_OFF;

	ret = usb_control_msg(usbdev, usb_sndctrlpipe(usbdev, 0),
			      K90_REQUEST_MACRO_MODE,
			      USB_DIR_OUT | USB_TYPE_VENDOR |
			      USB_RECIP_DEVICE, value, 0, NULL, 0,
			      USB_CTRL_SET_TIMEOUT);
	if (ret != 0)
		dev_warn(dev, "Failed to set record LED state (error: %d).\n",
			 ret);
}
