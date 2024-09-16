static struct se_wwn *srpt_make_tport(struct target_fabric_configfs *tf,
				      struct config_group *group,
				      const char *name)
{
	struct srpt_port *sport;
	int ret;

	sport = srpt_lookup_port(name);
	pr_debug("make_tport(%s)\n", name);
	ret = -EINVAL;
	if (!sport)
		goto err;

	return &sport->port_wwn;

err:
	return ERR_PTR(ret);
}
