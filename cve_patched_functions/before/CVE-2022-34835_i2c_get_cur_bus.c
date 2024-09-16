static int i2c_get_cur_bus(struct udevice **busp)
{
#ifdef CONFIG_I2C_SET_DEFAULT_BUS_NUM
	if (!i2c_cur_bus) {
		if (cmd_i2c_set_bus_num(CONFIG_I2C_DEFAULT_BUS_NUMBER)) {
			printf("Default I2C bus %d not found\n",
			       CONFIG_I2C_DEFAULT_BUS_NUMBER);
			return -ENODEV;
		}
	}
#endif

	if (!i2c_cur_bus) {
		puts("No I2C bus selected\n");
		return -ENODEV;
	}
	*busp = i2c_cur_bus;

	return 0;
}
