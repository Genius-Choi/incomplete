free_config_nic_rules(
	config_tree *ptree
	)
{
	nic_rule_node *curr_node;

	if (ptree->nic_rules != NULL) {
		while (1) {
			UNLINK_FIFO(curr_node, *ptree->nic_rules, link);
			if (NULL == curr_node)
				break;
			if (curr_node->if_name != NULL)
				free(curr_node->if_name);
			free(curr_node);
		}
		free(ptree->nic_rules);
		ptree->nic_rules = NULL;
	}
}
