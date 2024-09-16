static int su3000_identify_state(struct usb_device *udev,
				 struct dvb_usb_device_properties *props,
				 struct dvb_usb_device_description **desc,
				 int *cold)
{
	info("%s", __func__);

	*cold = 0;
	return 0;
}
