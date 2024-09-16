static int ds3000_frontend_attach(struct dvb_usb_adapter *d)
{
	struct dw2102_state *st = d->dev->priv;
	u8 obuf[] = {7, 1};

	d->fe_adap[0].fe = dvb_attach(ds3000_attach, &s660_ds3000_config,
			&d->dev->i2c_adap);

	if (d->fe_adap[0].fe == NULL)
		return -EIO;

	dvb_attach(ts2020_attach, d->fe_adap[0].fe, &s660_ts2020_config,
		&d->dev->i2c_adap);

	st->old_set_voltage = d->fe_adap[0].fe->ops.set_voltage;
	d->fe_adap[0].fe->ops.set_voltage = s660_set_voltage;

	dw210x_op_rw(d->dev->udev, 0x8a, 0, 0, obuf, 2, DW210X_WRITE_MSG);

	info("Attached ds3000+ts2020!");

	return 0;
}
