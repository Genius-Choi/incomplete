void server_connect_failed(SERVER_REC *server, const char *msg)
{
	g_return_if_fail(IS_SERVER(server));

	lookup_servers = g_slist_remove(lookup_servers, server);

	signal_emit("server connect failed", 2, server, msg);

	if (server->connect_tag != -1) {
		g_source_remove(server->connect_tag);
		server->connect_tag = -1;
	}
	if (server->handle != NULL) {
		net_sendbuffer_destroy(server->handle, TRUE);
		server->handle = NULL;
	}

	if (server->connect_pipe[0] != NULL) {
		g_io_channel_close(server->connect_pipe[0]);
		g_io_channel_unref(server->connect_pipe[0]);
		g_io_channel_close(server->connect_pipe[1]);
		g_io_channel_unref(server->connect_pipe[1]);
		server->connect_pipe[0] = NULL;
		server->connect_pipe[1] = NULL;
	}

	server_unref(server);
}
