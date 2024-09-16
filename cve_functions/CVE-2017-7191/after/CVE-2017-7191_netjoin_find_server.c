static NETJOIN_SERVER_REC *netjoin_find_server(IRC_SERVER_REC *server)
{
	GSList *tmp;

	g_return_val_if_fail(server != NULL, NULL);

	for (tmp = joinservers; tmp != NULL; tmp = tmp->next) {
		NETJOIN_SERVER_REC *rec = tmp->data;

		if (rec->server == server)
                        return rec;
	}

	return NULL;
}
