cmd_http_chunked(CMD_ARGS)
{
	struct http *hp;

	(void)cmd;
	(void)vl;
	CAST_OBJ_NOTNULL(hp, priv, HTTP_MAGIC);
	AN(av[1]);
	AZ(av[2]);
	VSB_clear(hp->vsb);
	VSB_printf(hp->vsb, "%jx%s%s%s",
	    (uintmax_t)strlen(av[1]), nl, av[1], nl);
	http_write(hp, 4, "chunked");
}
