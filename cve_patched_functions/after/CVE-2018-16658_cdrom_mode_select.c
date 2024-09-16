int cdrom_mode_select(struct cdrom_device_info *cdi,
		      struct packet_command *cgc)
{
	const struct cdrom_device_ops *cdo = cdi->ops;

	memset(cgc->cmd, 0, sizeof(cgc->cmd));
	memset(cgc->buffer, 0, 2);
	cgc->cmd[0] = GPCMD_MODE_SELECT_10;
	cgc->cmd[1] = 0x10;		/* PF */
	cgc->cmd[7] = cgc->buflen >> 8;
	cgc->cmd[8] = cgc->buflen & 0xff;
	cgc->data_direction = CGC_DATA_WRITE;
	return cdo->generic_packet(cdi, cgc);
}
