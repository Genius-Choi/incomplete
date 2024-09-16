void irc_servers_setup_init(void)
{
	settings_add_bool("server", "skip_motd", FALSE);
	settings_add_str("server", "alternate_nick", "");

	init_userinfo();
	signal_add("server setup fill reconn", (SIGNAL_FUNC) sig_server_setup_fill_reconn);
	signal_add("server setup fill connect", (SIGNAL_FUNC) sig_server_setup_fill_connect);
	signal_add("server setup fill chatnet", (SIGNAL_FUNC) sig_server_setup_fill_chatnet);
	signal_add("server setup read", (SIGNAL_FUNC) sig_server_setup_read);
	signal_add("server setup saved", (SIGNAL_FUNC) sig_server_setup_saved);
}
