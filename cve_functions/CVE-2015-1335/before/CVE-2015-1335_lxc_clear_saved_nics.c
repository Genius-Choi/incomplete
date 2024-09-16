static void lxc_clear_saved_nics(struct lxc_conf *conf)
{
	int i;

	if (!conf->saved_nics)
		return;
	for (i=0; i < conf->num_savednics; i++)
		free(conf->saved_nics[i].orig_name);
	free(conf->saved_nics);
}
