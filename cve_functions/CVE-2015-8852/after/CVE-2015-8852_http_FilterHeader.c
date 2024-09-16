http_FilterHeader(const struct sess *sp, unsigned how)
{
	struct http *hp;

	hp = sp->wrk->bereq;
	CHECK_OBJ_NOTNULL(hp, HTTP_MAGIC);
	hp->logtag = HTTP_Tx;

	http_copyh(hp, sp->http, HTTP_HDR_REQ);
	http_copyh(hp, sp->http, HTTP_HDR_URL);
	if (how == HTTPH_R_FETCH)
		http_SetH(hp, HTTP_HDR_PROTO, "HTTP/1.1");
	else
		http_copyh(hp, sp->http, HTTP_HDR_PROTO);
	http_FilterFields(sp->wrk, sp->fd, hp, sp->http, how);
	http_PrintfHeader(sp->wrk, sp->fd, hp, "X-Varnish: %u", sp->xid);
}
