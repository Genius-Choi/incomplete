static void sig_channel_created(CHANNEL_REC *channel)
{
	g_return_if_fail(IS_CHANNEL(channel));

	channel->nicks = g_hash_table_new((GHashFunc) g_istr_hash,
					  (GCompareFunc) g_istr_equal);
}
