void nicklist_rename_unique(SERVER_REC *server,
			    void *old_nick_id, const char *old_nick,
			    void *new_nick_id, const char *new_nick)
{
	nicklist_rename_list(server, new_nick_id, old_nick, new_nick,
			     nicklist_get_same_unique(server, old_nick_id));
}
