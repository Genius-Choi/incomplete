static int dw3101_frontend_attach(struct dvb_usb_adapter *d)
{
	d->fe_adap[0].fe = dvb_attach(tda10023_attach, &dw3101_tda10023_config,
				&d->dev->i2c_adap, 0x48);
	if (d->fe_adap[0].fe != NULL) {
		info("Attached tda10023!");
		return 0;
	}
	return -EIO;
}
