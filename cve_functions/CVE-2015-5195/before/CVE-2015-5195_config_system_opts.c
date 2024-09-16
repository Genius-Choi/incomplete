config_system_opts(
	config_tree *ptree
	)
{
	apply_enable_disable(ptree->enable_opts, 1);
	apply_enable_disable(ptree->disable_opts, 0);
}
