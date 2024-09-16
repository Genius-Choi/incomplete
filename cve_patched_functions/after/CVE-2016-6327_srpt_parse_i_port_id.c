static int srpt_parse_i_port_id(u8 i_port_id[16], const char *name)
{
	const char *p;
	unsigned len, count, leading_zero_bytes;
	int ret, rc;

	p = name;
	if (strncasecmp(p, "0x", 2) == 0)
		p += 2;
	ret = -EINVAL;
	len = strlen(p);
	if (len % 2)
		goto out;
	count = min(len / 2, 16U);
	leading_zero_bytes = 16 - count;
	memset(i_port_id, 0, leading_zero_bytes);
	rc = hex2bin(i_port_id + leading_zero_bytes, p, count);
	if (rc < 0)
		pr_debug("hex2bin failed for srpt_parse_i_port_id: %d\n", rc);
	ret = 0;
out:
	return ret;
}
