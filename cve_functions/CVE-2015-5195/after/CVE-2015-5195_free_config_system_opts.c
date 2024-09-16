free_config_system_opts(
	config_tree *ptree
	)
{
	FREE_ATTR_VAL_FIFO(ptree->enable_opts);
	FREE_ATTR_VAL_FIFO(ptree->disable_opts);
}
