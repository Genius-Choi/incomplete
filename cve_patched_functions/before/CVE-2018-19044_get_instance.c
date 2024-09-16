get_instance(void)
{
	char *conf_id = MALLOC(strlen(config_id) + 1);

	strcpy(conf_id, config_id);

	return conf_id;
}
