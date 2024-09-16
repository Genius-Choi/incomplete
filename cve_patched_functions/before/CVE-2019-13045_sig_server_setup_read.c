static void sig_server_setup_read(IRC_SERVER_SETUP_REC *rec, CONFIG_NODE *node)
{
	g_return_if_fail(rec != NULL);
	g_return_if_fail(node != NULL);

	if (!IS_IRC_SERVER_SETUP(rec))
		return;

	rec->max_cmds_at_once = config_node_get_int(node, "cmds_max_at_once", 0);
	rec->cmd_queue_speed = config_node_get_int(node, "cmd_queue_speed", 0);
	rec->max_query_chans = config_node_get_int(node, "max_query_chans", 0);
}
