static int do_i2c_flags(struct cmd_tbl *cmdtp, int flag, int argc,
			char *const argv[])
{
	struct udevice *dev;
	uint flags;
	int chip;
	int ret;

	if (argc < 2)
		return CMD_RET_USAGE;

	chip = hextoul(argv[1], NULL);
	ret = i2c_get_cur_bus_chip(chip, &dev);
	if (ret)
		return i2c_report_err(ret, I2C_ERR_READ);

	if (argc > 2) {
		flags = hextoul(argv[2], NULL);
		ret = i2c_set_chip_flags(dev, flags);
	} else  {
		ret = i2c_get_chip_flags(dev, &flags);
		if (!ret)
			printf("%x\n", flags);
	}
	if (ret)
		return i2c_report_err(ret, I2C_ERR_READ);

	return 0;
}
