static int su3000_streaming_ctrl(struct dvb_usb_adapter *adap, int onoff)
{
	static u8 command_start[] = {0x00};
	static u8 command_stop[] = {0x01};
	struct i2c_msg msg = {
		.addr = SU3000_STREAM_CTRL,
		.flags = 0,
		.buf = onoff ? command_start : command_stop,
		.len = 1
	};

	i2c_transfer(&adap->dev->i2c_adap, &msg, 1);

	return 0;
}
