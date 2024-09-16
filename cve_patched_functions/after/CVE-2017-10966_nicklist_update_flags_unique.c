void nicklist_update_flags_unique(SERVER_REC *server, void *id,
				  int gone, int serverop)
{
	nicklist_update_flags_list(server, gone, serverop,
				   nicklist_get_same_unique(server, id));
}
