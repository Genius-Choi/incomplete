static int netjoin_set_nickmode(IRC_SERVER_REC *server, NETJOIN_REC *rec,
				const char *channel, char prefix)
{
	GSList *pos;
	const char *flags;
	char *found_chan = NULL;

	for (pos = rec->now_channels; pos != NULL; pos = pos->next) {
		char *chan = pos->data;
		if (strcasecmp(chan+1, channel) == 0) {
			found_chan = chan;
			break;
		}
	}

	if (found_chan == NULL)
		return FALSE;

	flags = server->get_nick_flags(SERVER(server));
	while (*flags != '\0') {
		if (found_chan[0] == *flags)
			break;
		if (prefix == *flags) {
			found_chan[0] = prefix;
			break;
		}
		flags++;
	}
	return TRUE;
}
