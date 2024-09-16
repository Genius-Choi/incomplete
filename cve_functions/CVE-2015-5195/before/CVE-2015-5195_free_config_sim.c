free_config_sim(
	config_tree *ptree
	)
{
	sim_node *sim_n;
	server_info *serv_n;
	script_info *script_n;

	if (NULL == ptree->sim_details)
		return;
	sim_n = HEAD_PFIFO(ptree->sim_details);
	free(ptree->sim_details);
	ptree->sim_details = NULL;
	if (NULL == sim_n)
		return;

	FREE_ATTR_VAL_FIFO(sim_n->init_opts);
	while (1) {
		UNLINK_FIFO(serv_n, *sim_n->servers, link);
		if (NULL == serv_n)
			break;
		script_n = serv_n->curr_script;
		while (script_n != NULL) {
			free(script_n);
			if (serv_n->script != NULL)
				UNLINK_FIFO(script_n, *serv_n->script,
					    link);
			else
				break;
		}
		if (serv_n->script != NULL)
			free(serv_n->script);
		free(serv_n);
	}
	free(sim_n);
}
