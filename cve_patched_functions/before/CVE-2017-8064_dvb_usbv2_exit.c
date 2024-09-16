static int dvb_usbv2_exit(struct dvb_usb_device *d)
{
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	dvb_usbv2_remote_exit(d);
	dvb_usbv2_adapter_exit(d);
	dvb_usbv2_i2c_exit(d);
	kfree(d->priv);
	kfree(d);

	return 0;
}
