free_config_ttl(
	config_tree *ptree
	)
{
	FREE_INT_FIFO(ptree->ttl);
}
