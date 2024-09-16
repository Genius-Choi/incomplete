void server_change_nick(SERVER_REC *server, const char *nick)
{
	g_free(server->nick);
	server->nick = g_strdup(nick);

	signal_emit("server nick changed", 1, server);
}
