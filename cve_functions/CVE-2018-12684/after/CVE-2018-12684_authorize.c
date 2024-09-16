authorize(struct mg_connection *conn, struct mg_file *filep, const char *realm)
{
	struct read_auth_file_struct workdata;
	char buf[MG_BUF_LEN];

	if (!conn || !conn->dom_ctx) {
		return 0;
	}

	memset(&workdata, 0, sizeof(workdata));
	workdata.conn = conn;

	if (!parse_auth_header(conn, buf, sizeof(buf), &workdata.ah)) {
		return 0;
	}

	if (realm) {
		workdata.domain = realm;
	} else {
		workdata.domain = conn->dom_ctx->config[AUTHENTICATION_DOMAIN];
	}

	return read_auth_file(filep, &workdata, INITIAL_DEPTH);
}
