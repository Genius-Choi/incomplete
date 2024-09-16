static void handle_UNKNOWN(ctrl_t *ctrl, char *command)
{
	char buf[128];

	snprintf(buf, sizeof(buf), "500 command '%s' not recognized by server.\r\n", command);
	send_msg(ctrl->sd, buf);
}
