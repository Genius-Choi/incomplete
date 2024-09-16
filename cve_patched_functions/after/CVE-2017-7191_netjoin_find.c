static NETJOIN_REC *netjoin_find(IRC_SERVER_REC *server, const char *nick)
{
	NETJOIN_SERVER_REC *srec;
	GSList *tmp;

	g_return_val_if_fail(server != NULL, NULL);
	g_return_val_if_fail(nick != NULL, NULL);

	srec = netjoin_find_server(server);
        if (srec == NULL) return NULL;

	for (tmp = srec->netjoins; tmp != NULL; tmp = tmp->next) {
		NETJOIN_REC *rec = tmp->data;

		if (g_ascii_strcasecmp(rec->nick, nick) == 0)
			return rec;
	}

	return NULL;
}
