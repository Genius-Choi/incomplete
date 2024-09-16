static void netjoin_server_remove(NETJOIN_SERVER_REC *server)
{
	joinservers = g_slist_remove(joinservers, server);

	while (server->netjoins != NULL)
		netjoin_remove(server, server->netjoins->data);
        g_free(server);
}
