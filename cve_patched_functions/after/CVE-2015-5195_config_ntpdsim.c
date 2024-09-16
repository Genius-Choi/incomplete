config_ntpdsim(
	config_tree *ptree
	)
{
	printf("Configuring Simulator...\n");
	printf("Some ntpd-specific commands in the configuration file will be ignored.\n");

	config_tos(ptree);
	config_monitor(ptree);
	config_tinker(ptree);
	config_system_opts(ptree);
	config_logconfig(ptree);
	config_vars(ptree);
	config_sim(ptree);
}
