static void get_nicks_hash(gpointer key, NICK_REC *rec, GSList **list)
{
	while (rec != NULL) {
		*list = g_slist_prepend(*list, rec);
		rec = rec->next;
	}
}
