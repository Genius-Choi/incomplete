cmd_http_rxreq(CMD_ARGS)
{
	struct http *hp;

	(void)cmd;
	(void)vl;
	CAST_OBJ_NOTNULL(hp, priv, HTTP_MAGIC);
	ONLY_SERVER(hp, av);
	assert(!strcmp(av[0], "rxreq"));
	av++;

	for(; *av != NULL; av++)
		vtc_log(hp->vl, 0, "Unknown http rxreq spec: %s\n", *av);
	http_rxhdr(hp);
	http_splitheader(hp, 1);
	http_swallow_body(hp, hp->req, 0);
	vtc_log(hp->vl, 4, "bodylen = %s", hp->bodylen);
}
