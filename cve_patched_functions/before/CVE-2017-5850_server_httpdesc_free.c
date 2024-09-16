server_httpdesc_free(struct http_descriptor *desc)
{
	if (desc == NULL)
		return;

	free(desc->http_path);
	desc->http_path = NULL;
	free(desc->http_path_alias);
	desc->http_path_alias = NULL;
	free(desc->http_query);
	desc->http_query = NULL;
	free(desc->http_version);
	desc->http_version = NULL;
	free(desc->http_host);
	desc->http_host = NULL;

	kv_purge(&desc->http_headers);
	desc->http_lastheader = NULL;
	desc->http_method = 0;
	desc->http_chunked = 0;
}
