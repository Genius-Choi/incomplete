static int dvb_usbv2_device_power_ctrl(struct dvb_usb_device *d, int onoff)
{
	int ret;

	if (onoff)
		d->powered++;
	else
		d->powered--;

	if (d->powered == 0 || (onoff && d->powered == 1)) {
		/* when switching from 1 to 0 or from 0 to 1 */
		dev_dbg(&d->udev->dev, "%s: power=%d\n", __func__, onoff);
		if (d->props->power_ctrl) {
			ret = d->props->power_ctrl(d, onoff);
			if (ret < 0)
				goto err;
		}
	}

	return 0;
err:
	dev_dbg(&d->udev->dev, "%s: failed=%d\n", __func__, ret);
	return ret;
}
