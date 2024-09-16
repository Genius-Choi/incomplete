void lxc_rename_phys_nics_on_shutdown(int netnsfd, struct lxc_conf *conf)
{
	int i;

	if (conf->num_savednics == 0)
		return;

	INFO("running to reset %d nic names", conf->num_savednics);
	restore_phys_nics_to_netns(netnsfd, conf);
	for (i=0; i<conf->num_savednics; i++) {
		struct saved_nic *s = &conf->saved_nics[i];
		INFO("resetting nic %d to %s", s->ifindex, s->orig_name);
		lxc_netdev_rename_by_index(s->ifindex, s->orig_name);
		free(s->orig_name);
	}
	conf->num_savednics = 0;
}
