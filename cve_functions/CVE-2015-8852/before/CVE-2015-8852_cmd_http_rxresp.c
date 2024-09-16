cmd_http_rxresp(CMD_ARGS)
{
	struct http *hp;
	int has_obj = 1;

	(void)cmd;
	(void)vl;
	CAST_OBJ_NOTNULL(hp, priv, HTTP_MAGIC);
	ONLY_CLIENT(hp, av);
	assert(!strcmp(av[0], "rxresp"));
	av++;

	for(; *av != NULL; av++)
		if (!strcmp(*av, "-no_obj"))
			has_obj = 0;
		else
			vtc_log(hp->vl, 0,
			    "Unknown http rxresp spec: %s\n", *av);
	http_rxhdr(hp);
	http_splitheader(hp, 0);
	hp->body = hp->rxbuf + hp->prxbuf;
	if (!has_obj)
		return;
	else if (!strcmp(hp->resp[1], "200"))
		http_swallow_body(hp, hp->resp, 1);
	else
		http_swallow_body(hp, hp->resp, 0);
	vtc_log(hp->vl, 4, "bodylen = %s", hp->bodylen);
}
