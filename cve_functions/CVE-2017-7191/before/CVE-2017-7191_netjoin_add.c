static NETJOIN_REC *netjoin_add(IRC_SERVER_REC *server, const char *nick,
				GSList *channels)
{
	NETJOIN_REC *rec;
	NETJOIN_SERVER_REC *srec;

	g_return_val_if_fail(server != NULL, NULL);
	g_return_val_if_fail(nick != NULL, NULL);

	rec = g_new0(NETJOIN_REC, 1);
	rec->nick = g_strdup(nick);
	while (channels != NULL) {
		NETSPLIT_CHAN_REC *channel = channels->data;

		rec->old_channels = g_slist_append(rec->old_channels,
						   g_strdup(channel->name));
		channels = channels->next;
	}

	srec = netjoin_find_server(server);
	if (srec == NULL) {
		srec = g_new0(NETJOIN_SERVER_REC, 1);
		srec->server = server;
                joinservers = g_slist_append(joinservers, srec);
	}

	srec->last_netjoin = time(NULL);
	srec->netjoins = g_slist_append(srec->netjoins, rec);
	return rec;
}
