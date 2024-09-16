GSList *nicklist_getnicks(CHANNEL_REC *channel)
{
	GSList *list;

	g_return_val_if_fail(IS_CHANNEL(channel), NULL);

	list = NULL;
	g_hash_table_foreach(channel->nicks, (GHFunc) get_nicks_hash, &list);
	return list;
}
