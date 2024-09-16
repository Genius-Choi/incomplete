static void netjoin_remove(NETJOIN_SERVER_REC *server, NETJOIN_REC *rec)
{
	server->netjoins = g_slist_remove(server->netjoins, rec);

        g_slist_foreach(rec->old_channels, (GFunc) g_free, NULL);
	g_slist_foreach(rec->now_channels, (GFunc) g_free, NULL);
	g_slist_free(rec->old_channels);
	g_slist_free(rec->now_channels);

	g_free(rec->nick);
	g_free(rec);
}
