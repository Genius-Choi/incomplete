dump_all_config_trees(
	FILE *df,
	int comment
	) 
{
	config_tree *	cfg_ptr;
	int		return_value;

	return_value = 0;
	for (cfg_ptr = cfg_tree_history;
	     cfg_ptr != NULL; 
	     cfg_ptr = cfg_ptr->link) 
		return_value |= dump_config_tree(cfg_ptr, df, comment);

	return return_value;
}
