static int prof_rc_query(struct dvb_usb_device *d)
{
	u8 key[2];
	struct i2c_msg msg = {
		.addr = DW2102_RC_QUERY,
		.flags = I2C_M_RD,
		.buf = key,
		.len = 2
	};

	if (d->props.i2c_algo->master_xfer(&d->i2c_adap, &msg, 1) == 1) {
		if (msg.buf[0] != 0xff) {
			deb_rc("%s: rc code: %x, %x\n",
					__func__, key[0], key[1]);
			rc_keydown(d->rc_dev, RC_TYPE_UNKNOWN, key[0]^0xff, 0);
		}
	}

	return 0;
}
