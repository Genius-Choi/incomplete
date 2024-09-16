static void sig_server_reconnect_save_status(IRC_SERVER_CONNECT_REC *conn,
					     IRC_SERVER_REC *server)
{
	if (!IS_IRC_SERVER_CONNECT(conn) || !IS_IRC_SERVER(server) ||
	    !server->connected)
		return;

	g_free_not_null(conn->channels);
	conn->channels = irc_server_get_channels(server);

	g_free_not_null(conn->usermode);
	conn->usermode = g_strdup(server->wanted_usermode);
}
