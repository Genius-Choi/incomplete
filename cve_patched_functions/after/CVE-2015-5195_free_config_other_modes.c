free_config_other_modes(
	config_tree *ptree
	)
{
	FREE_ADDRESS_FIFO(ptree->manycastserver);
	FREE_ADDRESS_FIFO(ptree->multicastclient);
}
