static void nicklist_remove_hash(gpointer key, NICK_REC *nick,
				 CHANNEL_REC *channel)
{
	NICK_REC *next;

	while (nick != NULL) {
                next = nick->next;
		nicklist_destroy(channel, nick);
                nick = next;
	}
}
