free_config_setvar(
	config_tree *ptree
	)
{
	FREE_SETVAR_FIFO(ptree->setvar);
}
