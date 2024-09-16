GSList *nicklist_find_multiple(CHANNEL_REC *channel, const char *mask)
{
	GSList *nicks;
	NICK_REC *nick;
	GHashTableIter iter;

	g_return_val_if_fail(IS_CHANNEL(channel), NULL);
	g_return_val_if_fail(mask != NULL, NULL);

	nicks = NULL;

	g_hash_table_iter_init(&iter, channel->nicks);
	while (g_hash_table_iter_next(&iter, NULL, (void*)&nick)) {
		for (; nick != NULL; nick = nick->next) {
			if (mask_match_address(channel->server, mask,
					       nick->nick, nick->host))
				nicks = g_slist_prepend(nicks, nick);
		}
	}

	return nicks;
}
