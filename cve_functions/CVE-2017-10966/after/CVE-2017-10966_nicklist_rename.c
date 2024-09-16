void nicklist_rename(SERVER_REC *server, const char *old_nick,
		     const char *new_nick)
{
	nicklist_rename_list(server, NULL, old_nick, new_nick,
			     nicklist_get_same(server, old_nick));
}
