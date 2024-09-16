static int i2c_get_cur_bus_chip(uint chip_addr, struct udevice **devp)
{
	struct udevice *bus;
	int ret;

	ret = i2c_get_cur_bus(&bus);
	if (ret)
		return ret;

	return i2c_get_chip(bus, chip_addr, 1, devp);
}
