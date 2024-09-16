cmd_http_accept(CMD_ARGS)
{
	struct http *hp;

	(void)cmd;
	(void)vl;
	CAST_OBJ_NOTNULL(hp, priv, HTTP_MAGIC);
	AZ(av[1]);
	assert(hp->sfd != NULL);
	assert(*hp->sfd >= 0);
	if (hp->fd >= 0)
		VTCP_close(&hp->fd);
	vtc_log(vl, 4, "Accepting");
	hp->fd = accept(*hp->sfd, NULL, NULL);
	if (hp->fd < 0)
		vtc_log(vl, hp->fatal, "Accepted failed: %s", strerror(errno));
	vtc_log(vl, 3, "Accepted socket fd is %d", hp->fd);
}
