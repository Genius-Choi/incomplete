NICK_REC *nicklist_find_unique(CHANNEL_REC *channel, const char *nick,
			       void *id)
{
	NICK_REC *rec;

	g_return_val_if_fail(IS_CHANNEL(channel), NULL);
	g_return_val_if_fail(nick != NULL, NULL);

	rec = g_hash_table_lookup(channel->nicks, nick);
	while (rec != NULL && rec->unique_id != id)
                rec = rec->next;

        return rec;
}
