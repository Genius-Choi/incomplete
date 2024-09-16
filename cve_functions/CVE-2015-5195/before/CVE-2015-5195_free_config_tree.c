free_config_tree(
	config_tree *ptree
	)
{
#if defined(_MSC_VER) && defined (_DEBUG)
	_CrtCheckMemory();
#endif

	if (ptree->source.value.s != NULL)
		free(ptree->source.value.s);

	free_config_other_modes(ptree);
	free_config_auth(ptree);
	free_config_tos(ptree);
	free_config_monitor(ptree);
	free_config_access(ptree);
	free_config_tinker(ptree);
	free_config_system_opts(ptree);
	free_config_logconfig(ptree);
	free_config_phone(ptree);
	free_config_qos(ptree);
	free_config_setvar(ptree);
	free_config_ttl(ptree);
	free_config_trap(ptree);
	free_config_fudge(ptree);
	free_config_vars(ptree);
	free_config_peers(ptree);
	free_config_unpeers(ptree);
	free_config_nic_rules(ptree);
#ifdef SIM
	free_config_sim(ptree);
#endif
	free_auth_node(ptree);

	free(ptree);

#if defined(_MSC_VER) && defined (_DEBUG)
	_CrtCheckMemory();
#endif
}
