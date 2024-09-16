free_parser_data(void)
{
	if (LIST_EXISTS(defs))
		free_list(&defs);

	if (LIST_EXISTS(multiline_stack))
		free_list(&multiline_stack);
}
