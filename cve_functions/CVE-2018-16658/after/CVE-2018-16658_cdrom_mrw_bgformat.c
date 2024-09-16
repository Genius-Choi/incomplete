static int cdrom_mrw_bgformat(struct cdrom_device_info *cdi, int cont)
{
	struct packet_command cgc;
	unsigned char buffer[12];
	int ret;

	pr_info("%sstarting format\n", cont ? "Re" : "");

	/*
	 * FmtData bit set (bit 4), format type is 1
	 */
	init_cdrom_command(&cgc, buffer, sizeof(buffer), CGC_DATA_WRITE);
	cgc.cmd[0] = GPCMD_FORMAT_UNIT;
	cgc.cmd[1] = (1 << 4) | 1;

	cgc.timeout = 5 * 60 * HZ;

	/*
	 * 4 byte format list header, 8 byte format list descriptor
	 */
	buffer[1] = 1 << 1;
	buffer[3] = 8;

	/*
	 * nr_blocks field
	 */
	buffer[4] = 0xff;
	buffer[5] = 0xff;
	buffer[6] = 0xff;
	buffer[7] = 0xff;

	buffer[8] = 0x24 << 2;
	buffer[11] = cont;

	ret = cdi->ops->generic_packet(cdi, &cgc);
	if (ret)
		pr_info("bgformat failed\n");

	return ret;
}
