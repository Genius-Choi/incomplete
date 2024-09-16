int g_input_add(GIOChannel *source, int condition,
		GInputFunction function, void *data)
{
	return g_input_add_full(source, G_PRIORITY_DEFAULT, condition,
				function, data);
}
