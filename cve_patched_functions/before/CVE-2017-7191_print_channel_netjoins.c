static void print_channel_netjoins(char *channel, TEMP_PRINT_REC *rec,
				   NETJOIN_SERVER_REC *server)
{
	if (rec->nicks->len > 0)
		g_string_truncate(rec->nicks, rec->nicks->len-2);

	printformat(server->server, channel, MSGLEVEL_JOINS,
		    rec->count > netjoin_max_nicks ?
		    IRCTXT_NETSPLIT_JOIN_MORE : IRCTXT_NETSPLIT_JOIN,
		    rec->nicks->str, rec->count-netjoin_max_nicks);

	g_string_free(rec->nicks, TRUE);
	g_free(rec);
	g_free(channel);
}
