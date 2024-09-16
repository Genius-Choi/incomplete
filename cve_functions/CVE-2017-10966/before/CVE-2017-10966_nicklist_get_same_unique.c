GSList *nicklist_get_same_unique(SERVER_REC *server, void *id)
{
	NICKLIST_GET_SAME_UNIQUE_REC rec;
	GSList *tmp;

	g_return_val_if_fail(IS_SERVER(server), NULL);
	g_return_val_if_fail(id != NULL, NULL);

        rec.id = id;
	rec.list = NULL;
	for (tmp = server->channels; tmp != NULL; tmp = tmp->next) {
		rec.channel = tmp->data;
		g_hash_table_foreach(rec.channel->nicks,
				     (GHFunc) get_nicks_same_hash_unique,
				     &rec);
	}
	return rec.list;
}
