free_config_unpeers(
	config_tree *ptree
	)
{
	unpeer_node *curr_unpeer;

	if (ptree->unpeers != NULL) {
		while (1) {
			UNLINK_FIFO(curr_unpeer, *ptree->unpeers, link);
			if (NULL == curr_unpeer)
				break;
			destroy_address_node(curr_unpeer->addr);
			free(curr_unpeer);
		}
		free(ptree->unpeers);
	}
}
