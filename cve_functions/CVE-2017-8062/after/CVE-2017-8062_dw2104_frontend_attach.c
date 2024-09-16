static int dw2104_frontend_attach(struct dvb_usb_adapter *d)
{
	struct dvb_tuner_ops *tuner_ops = NULL;

	if (demod_probe & 4) {
		d->fe_adap[0].fe = dvb_attach(stv0900_attach, &dw2104a_stv0900_config,
				&d->dev->i2c_adap, 0);
		if (d->fe_adap[0].fe != NULL) {
			if (dvb_attach(stb6100_attach, d->fe_adap[0].fe,
					&dw2104a_stb6100_config,
					&d->dev->i2c_adap)) {
				tuner_ops = &d->fe_adap[0].fe->ops.tuner_ops;
				tuner_ops->set_frequency = stb6100_set_freq;
				tuner_ops->get_frequency = stb6100_get_freq;
				tuner_ops->set_bandwidth = stb6100_set_bandw;
				tuner_ops->get_bandwidth = stb6100_get_bandw;
				d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;
				info("Attached STV0900+STB6100!");
				return 0;
			}
		}
	}

	if (demod_probe & 2) {
		d->fe_adap[0].fe = dvb_attach(stv0900_attach, &dw2104_stv0900_config,
				&d->dev->i2c_adap, 0);
		if (d->fe_adap[0].fe != NULL) {
			if (dvb_attach(stv6110_attach, d->fe_adap[0].fe,
					&dw2104_stv6110_config,
					&d->dev->i2c_adap)) {
				d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;
				info("Attached STV0900+STV6110A!");
				return 0;
			}
		}
	}

	if (demod_probe & 1) {
		d->fe_adap[0].fe = dvb_attach(cx24116_attach, &dw2104_config,
				&d->dev->i2c_adap);
		if (d->fe_adap[0].fe != NULL) {
			d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;
			info("Attached cx24116!");
			return 0;
		}
	}

	d->fe_adap[0].fe = dvb_attach(ds3000_attach, &dw2104_ds3000_config,
			&d->dev->i2c_adap);
	if (d->fe_adap[0].fe != NULL) {
		dvb_attach(ts2020_attach, d->fe_adap[0].fe,
			&dw2104_ts2020_config, &d->dev->i2c_adap);
		d->fe_adap[0].fe->ops.set_voltage = dw210x_set_voltage;
		info("Attached DS3000!");
		return 0;
	}

	return -EIO;
}
