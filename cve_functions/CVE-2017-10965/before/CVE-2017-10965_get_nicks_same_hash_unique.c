static void get_nicks_same_hash_unique(gpointer key, NICK_REC *nick,
				       NICKLIST_GET_SAME_UNIQUE_REC *rec)
{
	while (nick != NULL) {
		if (nick->unique_id == rec->id) {
			rec->list = g_slist_append(rec->list, rec->channel);
			rec->list = g_slist_append(rec->list, nick);
                        break;
		}

                nick = nick->next;
	}
}
