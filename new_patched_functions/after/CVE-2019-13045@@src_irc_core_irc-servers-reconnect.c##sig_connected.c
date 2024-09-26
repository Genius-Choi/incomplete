static void sig_connected(IRC_SERVER_REC *server)
{
	if (!IS_IRC_SERVER(server) || !server->connrec->reconnection)
		return;

	if (server->connrec->away_reason != NULL)
		irc_server_send_away(server, server->connrec->away_reason);
}
