static void msg_quit(IRC_SERVER_REC *server, const char *nick,
		     const char *address, const char *reason)
{
	if (IS_IRC_SERVER(server) && quitmsg_is_split(reason))
		signal_stop();
}
