cmd_http_sendhex(CMD_ARGS)
{
	struct http *hp;
	char buf[3], *q;
	uint8_t *p;
	int i, j, l;

	(void)cmd;
	(void)vl;
	CAST_OBJ_NOTNULL(hp, priv, HTTP_MAGIC);
	AN(av[1]);
	AZ(av[2]);
	l = strlen(av[1]) / 2;
	p = malloc(l);
	AN(p);
	q = av[1];
	for (i = 0; i < l; i++) {
		while (vct_issp(*q))
			q++;
		if (*q == '\0')
			break;
		memcpy(buf, q, 2);
		q += 2;
		buf[2] = '\0';
		if (!vct_ishex(buf[0]) || !vct_ishex(buf[1]))
			vtc_log(hp->vl, 0, "Illegal Hex char \"%c%c\"",
			    buf[0], buf[1]);
		p[i] = (uint8_t)strtoul(buf, NULL, 16);
	}
	vtc_hexdump(hp->vl, 4, "sendhex", (void*)p, i);
	j = write(hp->fd, p, i);
	assert(j == i);
	free(p);

}
