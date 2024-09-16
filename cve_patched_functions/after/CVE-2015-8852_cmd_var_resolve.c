cmd_var_resolve(struct http *hp, char *spec)
{
	char **hh, *hdr;

	if (!strcmp(spec, "req.request"))
		return(hp->req[0]);
	if (!strcmp(spec, "req.url"))
		return(hp->req[1]);
	if (!strcmp(spec, "req.proto"))
		return(hp->req[2]);
	if (!strcmp(spec, "resp.proto"))
		return(hp->resp[0]);
	if (!strcmp(spec, "resp.status"))
		return(hp->resp[1]);
	if (!strcmp(spec, "resp.msg"))
		return(hp->resp[2]);
	if (!strcmp(spec, "resp.chunklen"))
		return(hp->chunklen);
	if (!strcmp(spec, "resp.bodylen"))
		return(hp->bodylen);
	if (!strcmp(spec, "resp.body"))
		return(hp->body != NULL ? hp->body : spec);
	if (!memcmp(spec, "req.http.", 9)) {
		hh = hp->req;
		hdr = spec + 9;
	} else if (!memcmp(spec, "resp.http.", 10)) {
		hh = hp->resp;
		hdr = spec + 10;
	} else
		return (spec);
	hdr = http_find_header(hh, hdr);
	if (hdr != NULL)
		return (hdr);
	return ("<undef>");
}
