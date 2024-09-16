free_config_trap(
	config_tree *ptree
	)
{
	FREE_ADDR_OPTS_FIFO(ptree->trap);
}
