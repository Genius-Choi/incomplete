static int server_remove_channels(SERVER_REC *server)
{
	GSList *tmp, *next;
	int found;

	g_return_val_if_fail(server != NULL, FALSE);

	found = FALSE;
	for (tmp = server->channels; tmp != NULL; tmp = next) {
		CHANNEL_REC *channel = tmp->data;

		next = tmp->next;
		channel_destroy(channel);
		found = TRUE;
	}

	while (server->queries != NULL)
		query_change_server(server->queries->data, NULL);

	g_slist_free(server->channels);
	g_slist_free(server->queries);

	return found;
}
