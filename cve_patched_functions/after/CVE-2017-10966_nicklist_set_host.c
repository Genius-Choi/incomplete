void nicklist_set_host(CHANNEL_REC *channel, NICK_REC *nick, const char *host)
{
        g_return_if_fail(channel != NULL);
        g_return_if_fail(nick != NULL);
	g_return_if_fail(host != NULL);

        g_free_not_null(nick->host);
	nick->host = g_strdup(host);

        signal_emit("nicklist host changed", 2, channel, nick);
}
