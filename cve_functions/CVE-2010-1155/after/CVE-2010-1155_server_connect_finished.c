void server_connect_finished(SERVER_REC *server)
{
	server->connect_time = time(NULL);

	servers = g_slist_append(servers, server);
	signal_emit("server connected", 1, server);
}
