int g_input_add_poll(int fd, int priority, int condition,
		     GInputFunction function, void *data)
{
	GIOChannel *source = g_io_channel_unix_new(fd);
	int ret = g_input_add_full(source, priority, condition, function, data);
	g_io_channel_unref(source);
	return ret;
}
