static int stv0288_frontend_attach(struct dvb_usb_adapter *d)
{
	u8 obuf[] = {7, 1};

	d->fe_adap[0].fe = dvb_attach(stv0288_attach, &earda_config,
			&d->dev->i2c_adap);

	if (d->fe_adap[0].fe == NULL)
		return -EIO;

	if (NULL == dvb_attach(stb6000_attach, d->fe_adap[0].fe, 0x61, &d->dev->i2c_adap))
		return -EIO;

	d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;

	dw210x_op_rw(d->dev->udev, 0x8a, 0, 0, obuf, 2, DW210X_WRITE_MSG);

	info("Attached stv0288+stb6000!");

	return 0;

}
