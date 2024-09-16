static int cmd_i2c_set_bus_num(unsigned int busnum)
{
	struct udevice *bus;
	int ret;

	ret = uclass_get_device_by_seq(UCLASS_I2C, busnum, &bus);
	if (ret) {
		debug("%s: No bus %d\n", __func__, busnum);
		return ret;
	}
	i2c_cur_bus = bus;

	return 0;
}
