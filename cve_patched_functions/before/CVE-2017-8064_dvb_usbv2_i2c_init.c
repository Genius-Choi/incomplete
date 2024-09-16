static int dvb_usbv2_i2c_init(struct dvb_usb_device *d)
{
	int ret;
	dev_dbg(&d->udev->dev, "%s:\n", __func__);

	if (!d->props->i2c_algo)
		return 0;

	strlcpy(d->i2c_adap.name, d->name, sizeof(d->i2c_adap.name));
	d->i2c_adap.algo = d->props->i2c_algo;
	d->i2c_adap.dev.parent = &d->udev->dev;
	i2c_set_adapdata(&d->i2c_adap, d);

	ret = i2c_add_adapter(&d->i2c_adap);
	if (ret < 0) {
		d->i2c_adap.algo = NULL;
		goto err;
	}

	return 0;
err:
	dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);
	return ret;
}
