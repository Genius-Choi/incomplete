cmd_http_timeout(CMD_ARGS)
{
	struct http *hp;

	(void)cmd;
	(void)vl;
	CAST_OBJ_NOTNULL(hp, priv, HTTP_MAGIC);
	AN(av[1]);
	AZ(av[2]);
	hp->timeout = (int)(strtod(av[1], NULL) * 1000.0);
}
