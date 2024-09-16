static int pcd_packet(struct cdrom_device_info *cdi, struct packet_command *cgc)
{
	return pcd_atapi(cdi->handle, cgc->cmd, cgc->buflen, cgc->buffer,
			 "generic packet");
}
