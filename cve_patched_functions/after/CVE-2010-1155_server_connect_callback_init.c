static void server_connect_callback_init(SERVER_REC *server, GIOChannel *handle)
{
	int error;

	g_return_if_fail(IS_SERVER(server));

	error = net_geterror(handle);
	if (error != 0) {
		server->connection_lost = TRUE;
		server_connect_failed(server, g_strerror(error));
		return;
	}

	lookup_servers = g_slist_remove(lookup_servers, server);
	g_source_remove(server->connect_tag);
	server->connect_tag = -1;

	server_connect_finished(server);
}
