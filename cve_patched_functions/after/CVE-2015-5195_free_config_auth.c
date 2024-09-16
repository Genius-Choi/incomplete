free_config_auth(
	config_tree *ptree
	)
{
	destroy_attr_val_fifo(ptree->auth.crypto_cmd_list);
	ptree->auth.crypto_cmd_list = NULL;
	destroy_attr_val_fifo(ptree->auth.trusted_key_list);
	ptree->auth.trusted_key_list = NULL;
}
