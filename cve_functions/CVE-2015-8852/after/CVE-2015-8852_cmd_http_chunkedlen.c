cmd_http_chunkedlen(CMD_ARGS)
{
	unsigned len;
	unsigned u, v;
	char buf[16384];
	struct http *hp;

	(void)cmd;
	(void)vl;
	CAST_OBJ_NOTNULL(hp, priv, HTTP_MAGIC);
	AN(av[1]);
	AZ(av[2]);
	VSB_clear(hp->vsb);

	len = atoi(av[1]);

	if (len == 0) {
		VSB_printf(hp->vsb, "0%s%s", nl, nl);
	} else {
		for (u = 0; u < sizeof buf; u++)
			buf[u] = (u & 7) + '0';

		VSB_printf(hp->vsb, "%x%s", len, nl);
		for (u = 0; u < len; u += v) {
			v = len - u;
			if (v > sizeof buf)
				v = sizeof buf;
			VSB_bcat(hp->vsb, buf, v);
		}
		VSB_printf(hp->vsb, "%s", nl);
	}
	http_write(hp, 4, "chunked");
}
