cmd_http_txreq(CMD_ARGS)
{
	struct http *hp;
	const char *req = "GET";
	const char *url = "/";
	const char *proto = "HTTP/1.1";
	const char *body = NULL;

	(void)cmd;
	(void)vl;
	CAST_OBJ_NOTNULL(hp, priv, HTTP_MAGIC);
	ONLY_CLIENT(hp, av);
	assert(!strcmp(av[0], "txreq"));
	av++;

	VSB_clear(hp->vsb);

	for(; *av != NULL; av++) {
		if (!strcmp(*av, "-url")) {
			url = av[1];
			av++;
		} else if (!strcmp(*av, "-proto")) {
			proto = av[1];
			av++;
		} else if (!strcmp(*av, "-req")) {
			req = av[1];
			av++;
		} else
			break;
	}
	VSB_printf(hp->vsb, "%s %s %s%s", req, url, proto, nl);
	for(; *av != NULL; av++) {
		if (!strcmp(*av, "-hdr")) {
			VSB_printf(hp->vsb, "%s%s", av[1], nl);
			av++;
		} else
			break;
	}
	for(; *av != NULL; av++) {
		if (!strcmp(*av, "-body")) {
			AZ(body);
			body = av[1];
			av++;
		} else if (!strcmp(*av, "-bodylen")) {
			AZ(body);
			body = synth_body(av[1], 0);
			av++;
		} else
			break;
	}
	if (*av != NULL)
		vtc_log(hp->vl, 0, "Unknown http txreq spec: %s\n", *av);
	if (body != NULL)
		VSB_printf(hp->vsb, "Content-Length: %ju%s",
		    (uintmax_t)strlen(body), nl);
	VSB_cat(hp->vsb, nl);
	if (body != NULL) {
		VSB_cat(hp->vsb, body);
		VSB_cat(hp->vsb, nl);
	}
	http_write(hp, 4, "txreq");
}
