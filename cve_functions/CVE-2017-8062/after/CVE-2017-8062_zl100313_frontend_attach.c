static int zl100313_frontend_attach(struct dvb_usb_adapter *d)
{
	d->fe_adap[0].fe = dvb_attach(mt312_attach, &zl313_config,
			&d->dev->i2c_adap);
	if (d->fe_adap[0].fe != NULL) {
		if (dvb_attach(zl10039_attach, d->fe_adap[0].fe, 0x60,
				&d->dev->i2c_adap)) {
			d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;
			info("Attached zl100313+zl10039!");
			return 0;
		}
	}

	return -EIO;
}
