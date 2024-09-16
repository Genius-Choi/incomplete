cmd_http_close(CMD_ARGS)
{
	struct http *hp;

	(void)cmd;
	(void)vl;
	CAST_OBJ_NOTNULL(hp, priv, HTTP_MAGIC);
	AZ(av[1]);
	assert(hp->sfd != NULL);
	assert(*hp->sfd >= 0);
	VTCP_close(&hp->fd);
	vtc_log(vl, 4, "Closed");
}
