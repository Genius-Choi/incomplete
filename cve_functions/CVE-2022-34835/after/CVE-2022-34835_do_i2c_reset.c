static int do_i2c_reset(struct cmd_tbl *cmdtp, int flag, int argc,
			char *const argv[])
{
#if CONFIG_IS_ENABLED(DM_I2C)
	struct udevice *bus;

	if (i2c_get_cur_bus(&bus))
		return CMD_RET_FAILURE;
	if (i2c_deblock(bus)) {
		printf("Error: Not supported by the driver\n");
		return CMD_RET_FAILURE;
	}
#elif CONFIG_IS_ENABLED(SYS_I2C_LEGACY)
	i2c_init(I2C_ADAP->speed, I2C_ADAP->slaveaddr);
#endif
	return 0;
}
