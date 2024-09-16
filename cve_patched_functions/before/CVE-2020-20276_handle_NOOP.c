static void handle_NOOP(ctrl_t *ctrl, char *arg)
{
	send_msg(ctrl->sd, "200 NOOP OK.\r\n");
}
