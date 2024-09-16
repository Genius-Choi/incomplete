static void sig_server_setup_fill_connect(IRC_SERVER_CONNECT_REC *conn)
{
	const char *value;

	if (!IS_IRC_SERVER_CONNECT(conn))
		return;

	value = settings_get_str("alternate_nick");
	conn->alternate_nick = (value != NULL && *value != '\0') ?
		g_strdup(value) : NULL;

	value = settings_get_str("usermode");
	conn->usermode = (value != NULL && *value != '\0') ?
		g_strdup(value) : NULL;
}
