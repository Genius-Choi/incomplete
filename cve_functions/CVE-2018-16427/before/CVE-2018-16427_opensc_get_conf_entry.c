static int opensc_get_conf_entry(const char *config)
{
	scconf_block *conf_block = NULL, **blocks;
	char *buffer = NULL;
	char *section = NULL;
	char *name = NULL;
	char *key = NULL;
	int r = 0;

	if (ctx->conf == NULL) {
		r = ENOENT;
		goto cleanup;
	}

	if ((buffer = strdup(config)) == NULL) {
		r = ENOMEM;
		goto cleanup;
	}

	section = buffer;
	name = strchr(section+1, ':');
	key = name == NULL ? NULL : strchr(name+1, ':');
	if (key == NULL) {
		r = EINVAL;
		goto cleanup;
	}
	*name = '\0';
	name++;
	*key = '\0';
	key++;

	blocks = scconf_find_blocks(ctx->conf, NULL, section, name);
	if (blocks && blocks[0])
		conf_block = blocks[0];
	free(blocks);
	if (conf_block != NULL) {
		const char *value = scconf_get_str(conf_block, key, NULL);

		if (value != NULL) {
			printf ("%s\n", value);
		}
	}

	r = 0;

cleanup:

	if (buffer != NULL)
		free(buffer);

	return r;
}
