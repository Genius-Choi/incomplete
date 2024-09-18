int g_input_add_full(GIOChannel *source, int priority, int condition,
		     GInputFunction function, void *data)
{
        IRSSI_INPUT_REC *rec;
	unsigned int result;
	GIOCondition cond;

	rec = g_new(IRSSI_INPUT_REC, 1);
	rec->condition = condition;
	rec->function = function;
	rec->data = data;

	cond = (GIOCondition) (G_IO_ERR|G_IO_HUP|G_IO_NVAL);
	if (condition & G_INPUT_READ)
		cond |= G_IO_IN|G_IO_PRI;
	if (condition & G_INPUT_WRITE)
		cond |= G_IO_OUT;

	result = g_io_add_watch_full(source, priority, cond,
				     irssi_io_invoke, rec, g_free);

	return result;
}
