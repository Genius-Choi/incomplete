static int dw210x_set_voltage(struct dvb_frontend *fe,
			      enum fe_sec_voltage voltage)
{
	static u8 command_13v[] = {0x00, 0x01};
	static u8 command_18v[] = {0x01, 0x01};
	static u8 command_off[] = {0x00, 0x00};
	struct i2c_msg msg = {
		.addr = DW2102_VOLTAGE_CTRL,
		.flags = 0,
		.buf = command_off,
		.len = 2,
	};

	struct dvb_usb_adapter *udev_adap =
		(struct dvb_usb_adapter *)(fe->dvb->priv);
	if (voltage == SEC_VOLTAGE_18)
		msg.buf = command_18v;
	else if (voltage == SEC_VOLTAGE_13)
		msg.buf = command_13v;

	i2c_transfer(&udev_adap->dev->i2c_adap, &msg, 1);

	return 0;
}
