get_option_index(const char *name)
{
	int i;

	for (i = 0; config_options[i].name != NULL; i++) {
		if (strcmp(config_options[i].name, name) == 0) {
			return i;
		}
	}
	return -1;
}
