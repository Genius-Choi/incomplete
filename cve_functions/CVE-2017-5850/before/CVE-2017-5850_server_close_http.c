server_close_http(struct client *clt)
{
	struct http_descriptor *desc;

	desc = clt->clt_descreq;
	server_httpdesc_free(desc);
	free(desc);
	clt->clt_descreq = NULL;

	desc = clt->clt_descresp;
	server_httpdesc_free(desc);
	free(desc);
	clt->clt_descresp = NULL;
	free(clt->clt_remote_user);
	clt->clt_remote_user = NULL;

	str_match_free(&clt->clt_srv_match);
}
