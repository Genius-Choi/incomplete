free_config_monitor(
	config_tree *ptree
	)
{
	if (ptree->stats_dir) {
		free(ptree->stats_dir);
		ptree->stats_dir = NULL;
	}

	FREE_INT_FIFO(ptree->stats_list);
	FREE_FILEGEN_FIFO(ptree->filegen_opts);
}
