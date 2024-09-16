void server_connect_init(SERVER_REC *server)
{
	const char *str;

	g_return_if_fail(server != NULL);

	MODULE_DATA_INIT(server);
	server->type = module_get_uniq_id("SERVER", 0);
	server_ref(server);

	server->nick = g_strdup(server->connrec->nick);
	if (server->connrec->username == NULL || *server->connrec->username == '\0') {
		g_free_not_null(server->connrec->username);

		str = g_get_user_name();
		if (*str == '\0') str = "unknown";
		server->connrec->username = g_strdup(str);
	}
	if (server->connrec->realname == NULL || *server->connrec->realname == '\0') {
		g_free_not_null(server->connrec->realname);

		str = g_get_real_name();
		if (*str == '\0') str = server->connrec->username;
		server->connrec->realname = g_strdup(str);
	}

	server->tag = server_create_tag(server->connrec);
	server->connect_tag = -1;
}
