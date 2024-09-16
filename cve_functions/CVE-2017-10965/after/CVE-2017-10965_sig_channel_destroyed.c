static void sig_channel_destroyed(CHANNEL_REC *channel)
{
	g_return_if_fail(IS_CHANNEL(channel));

	g_hash_table_foreach(channel->nicks,
			     (GHFunc) nicklist_remove_hash, channel);
	g_hash_table_destroy(channel->nicks);
}
