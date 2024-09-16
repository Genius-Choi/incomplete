void nicklist_update_flags(SERVER_REC *server, const char *nick,
			   int gone, int serverop)
{
	nicklist_update_flags_list(server, gone, serverop,
				   nicklist_get_same(server, nick));
}
