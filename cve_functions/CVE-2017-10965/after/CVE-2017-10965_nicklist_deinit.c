void nicklist_deinit(void)
{
	signal_remove("channel created", (SIGNAL_FUNC) sig_channel_created);
	signal_remove("channel destroyed", (SIGNAL_FUNC) sig_channel_destroyed);

	module_uniq_destroy("NICK");
}
