void irc_servers_reconnect_init(void)
{
	signal_add("server connect copy", (SIGNAL_FUNC) sig_server_connect_copy);
	signal_add("server reconnect save status", (SIGNAL_FUNC) sig_server_reconnect_save_status);
	signal_add("event connected", (SIGNAL_FUNC) sig_connected);
	signal_add("event 436", (SIGNAL_FUNC) event_nick_collision);
	signal_add("event kill", (SIGNAL_FUNC) event_kill);
}
