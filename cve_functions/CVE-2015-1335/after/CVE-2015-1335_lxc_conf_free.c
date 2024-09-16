void lxc_conf_free(struct lxc_conf *conf)
{
	if (!conf)
		return;
	if (current_config == conf)
		current_config = NULL;
	free(conf->console.log_path);
	free(conf->console.path);
	free(conf->rootfs.mount);
	free(conf->rootfs.options);
	free(conf->rootfs.path);
	free(conf->rootfs.pivot);
	free(conf->logfile);
	if (conf->logfd != -1)
		close(conf->logfd);
	free(conf->utsname);
	free(conf->ttydir);
	free(conf->fstab);
	free(conf->rcfile);
	free(conf->init_cmd);
	free(conf->unexpanded_config);
	free(conf->pty_names);
	lxc_clear_config_network(conf);
	free(conf->lsm_aa_profile);
	free(conf->lsm_se_context);
	lxc_seccomp_free(conf);
	lxc_clear_config_caps(conf);
	lxc_clear_config_keepcaps(conf);
	lxc_clear_cgroups(conf, "lxc.cgroup");
	lxc_clear_hooks(conf, "lxc.hook");
	lxc_clear_mount_entries(conf);
	lxc_clear_saved_nics(conf);
	lxc_clear_idmaps(conf);
	lxc_clear_groups(conf);
	lxc_clear_includes(conf);
	lxc_clear_aliens(conf);
	lxc_clear_environment(conf);
	free(conf);
}
