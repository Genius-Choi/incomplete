free_config_tos(
	config_tree *ptree
	)
{
	FREE_ATTR_VAL_FIFO(ptree->orphan_cmds);
}
