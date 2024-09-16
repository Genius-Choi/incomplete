static void nicklist_update_flags_list(SERVER_REC *server, int gone,
				       int serverop, GSList *nicks)
{
	GSList *tmp;
	CHANNEL_REC *channel;
	NICK_REC *rec;

	g_return_if_fail(IS_SERVER(server));

	for (tmp = nicks; tmp != NULL; tmp = tmp->next->next) {
		channel = tmp->data;
		rec = tmp->next->data;

		rec->last_check = time(NULL);

		if (gone != -1 && (int)rec->gone != gone) {
			rec->gone = gone;
			signal_emit("nicklist gone changed", 2, channel, rec);
		}

		if (serverop != -1 && (int)rec->serverop != serverop) {
			rec->serverop = serverop;
			signal_emit("nicklist serverop changed", 2, channel, rec);
		}
	}
	g_slist_free(nicks);
}
