void nicklist_remove(CHANNEL_REC *channel, NICK_REC *nick)
{
	g_return_if_fail(IS_CHANNEL(channel));
	g_return_if_fail(nick != NULL);

        nick_hash_remove(channel, nick);
	nicklist_destroy(channel, nick);
}
