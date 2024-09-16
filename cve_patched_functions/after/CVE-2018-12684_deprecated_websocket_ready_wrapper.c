deprecated_websocket_ready_wrapper(struct mg_connection *conn, void *cbdata)
{
	struct mg_callbacks *pcallbacks = (struct mg_callbacks *)cbdata;
	if (pcallbacks->websocket_ready) {
		pcallbacks->websocket_ready(conn);
	}
}
