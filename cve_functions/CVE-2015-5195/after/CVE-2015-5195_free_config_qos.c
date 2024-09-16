free_config_qos(
	config_tree *ptree
	)
{
	FREE_ATTR_VAL_FIFO(ptree->qos);
}
