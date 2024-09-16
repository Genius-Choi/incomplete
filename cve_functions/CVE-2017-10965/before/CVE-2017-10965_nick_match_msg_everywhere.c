int nick_match_msg_everywhere(CHANNEL_REC *channel, const char *msg, const char *nick)
{
	g_return_val_if_fail(nick != NULL, FALSE);
	g_return_val_if_fail(msg != NULL, FALSE);

	return stristr_full(msg, nick) != NULL;
}
