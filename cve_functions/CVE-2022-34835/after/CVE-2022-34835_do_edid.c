int do_edid(struct cmd_tbl *cmdtp, int flag, int argc, char *const argv[])
{
	uint chip;
	struct edid1_info edid;
	int ret;
#if CONFIG_IS_ENABLED(DM_I2C)
	struct udevice *dev;
#endif

	if (argc < 2) {
		cmd_usage(cmdtp);
		return 1;
	}

	chip = hextoul(argv[1], NULL);
#if CONFIG_IS_ENABLED(DM_I2C)
	ret = i2c_get_cur_bus_chip(chip, &dev);
	if (!ret)
		ret = dm_i2c_read(dev, 0, (uchar *)&edid, sizeof(edid));
#else
	ret = i2c_read(chip, 0, 1, (uchar *)&edid, sizeof(edid));
#endif
	if (ret)
		return i2c_report_err(ret, I2C_ERR_READ);

	if (edid_check_info(&edid)) {
		puts("Content isn't valid EDID.\n");
		return 1;
	}

	edid_print_info(&edid);
	return 0;

}
