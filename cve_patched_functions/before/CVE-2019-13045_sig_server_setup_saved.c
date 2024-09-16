static void sig_server_setup_saved(IRC_SERVER_SETUP_REC *rec,
				   CONFIG_NODE *node)
{
	if (!IS_IRC_SERVER_SETUP(rec))
		return;

	if (rec->max_cmds_at_once > 0)
		iconfig_node_set_int(node, "cmds_max_at_once", rec->max_cmds_at_once);
	if (rec->cmd_queue_speed > 0)
		iconfig_node_set_int(node, "cmd_queue_speed", rec->cmd_queue_speed);
	if (rec->max_query_chans > 0)
		iconfig_node_set_int(node, "max_query_chans", rec->max_query_chans);
}
