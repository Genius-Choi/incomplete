static int i2c_report_err(int ret, enum i2c_err_op op)
{
	printf("Error %s the chip: %d\n",
	       op == I2C_ERR_READ ? "reading" : "writing", ret);

	return CMD_RET_FAILURE;
}
