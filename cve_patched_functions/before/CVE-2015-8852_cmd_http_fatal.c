cmd_http_fatal(CMD_ARGS)
{
	struct http *hp;
	CAST_OBJ_NOTNULL(hp, priv, HTTP_MAGIC);

	AZ(av[1]);
	if (!strcmp(av[0], "fatal"))
		hp->fatal = 0;
	else if (!strcmp(av[0], "non-fatal"))
		hp->fatal = -1;
	else {
		vtc_log(vl, 0, "XXX: fatal %s", cmd->name);
	}
}
