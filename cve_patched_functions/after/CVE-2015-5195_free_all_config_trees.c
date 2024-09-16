free_all_config_trees(void)
{
	config_tree *ptree;
	config_tree *pnext;

	ptree = cfg_tree_history;

	while (ptree != NULL) {
		pnext = ptree->link;
		free_config_tree(ptree);
		ptree = pnext;
	}
}
