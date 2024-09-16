void servers_deinit(void)
{
	signal_remove("chat protocol deinit", (SIGNAL_FUNC) sig_chat_protocol_deinit);

	servers_setup_deinit();
	servers_reconnect_deinit();

	module_uniq_destroy("SERVER");
	module_uniq_destroy("SERVER CONNECT");
}
