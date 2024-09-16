static NICK_REC *nicklist_find_wildcards(CHANNEL_REC *channel,
					 const char *mask)
{
	NICK_REC *nick;
	GHashTableIter iter;

	g_hash_table_iter_init(&iter, channel->nicks);
	while (g_hash_table_iter_next(&iter, NULL, (void*)&nick)) {
		for (; nick != NULL; nick = nick->next) {
			if (mask_match_address(channel->server, mask,
					       nick->nick, nick->host))
				return nick;
		}
	}

	return NULL;
}
