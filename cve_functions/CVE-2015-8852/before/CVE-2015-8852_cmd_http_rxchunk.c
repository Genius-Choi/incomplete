cmd_http_rxchunk(CMD_ARGS)
{
	struct http *hp;
	int ll, i;

	(void)cmd;
	(void)vl;
	CAST_OBJ_NOTNULL(hp, priv, HTTP_MAGIC);
	ONLY_CLIENT(hp, av);

	i = http_rxchunk(hp);
	if (i == 0) {
		ll = hp->rxbuf + hp->prxbuf - hp->body;
		hp->bodyl = ll;
		sprintf(hp->bodylen, "%d", ll);
		vtc_log(hp->vl, 4, "bodylen = %s", hp->bodylen);
	}
}
