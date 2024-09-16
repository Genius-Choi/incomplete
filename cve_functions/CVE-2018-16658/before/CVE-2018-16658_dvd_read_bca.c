static int dvd_read_bca(struct cdrom_device_info *cdi, dvd_struct *s,
			struct packet_command *cgc)
{
	int ret, size = 4 + 188;
	u_char *buf;
	const struct cdrom_device_ops *cdo = cdi->ops;

	buf = kmalloc(size, GFP_KERNEL);
	if (!buf)
		return -ENOMEM;

	init_cdrom_command(cgc, buf, size, CGC_DATA_READ);
	cgc->cmd[0] = GPCMD_READ_DVD_STRUCTURE;
	cgc->cmd[7] = s->type;
	cgc->cmd[9] = cgc->buflen & 0xff;

	ret = cdo->generic_packet(cdi, cgc);
	if (ret)
		goto out;

	s->bca.len = buf[0] << 8 | buf[1];
	if (s->bca.len < 12 || s->bca.len > 188) {
		cd_dbg(CD_WARNING, "Received invalid BCA length (%d)\n",
		       s->bca.len);
		ret = -EIO;
		goto out;
	}
	memcpy(s->bca.value, &buf[4], s->bca.len);
	ret = 0;
out:
	kfree(buf);
	return ret;
}
