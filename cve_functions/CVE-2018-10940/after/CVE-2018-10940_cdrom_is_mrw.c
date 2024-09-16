static int cdrom_is_mrw(struct cdrom_device_info *cdi, int *write)
{
	struct packet_command cgc;
	struct mrw_feature_desc *mfd;
	unsigned char buffer[16];
	int ret;

	*write = 0;

	init_cdrom_command(&cgc, buffer, sizeof(buffer), CGC_DATA_READ);

	cgc.cmd[0] = GPCMD_GET_CONFIGURATION;
	cgc.cmd[3] = CDF_MRW;
	cgc.cmd[8] = sizeof(buffer);
	cgc.quiet = 1;

	if ((ret = cdi->ops->generic_packet(cdi, &cgc)))
		return ret;

	mfd = (struct mrw_feature_desc *)&buffer[sizeof(struct feature_header)];
	if (be16_to_cpu(mfd->feature_code) != CDF_MRW)
		return 1;
	*write = mfd->write;

	if ((ret = cdrom_mrw_probe_pc(cdi))) {
		*write = 0;
		return ret;
	}

	return 0;
}
