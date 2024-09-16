static void handle_QUIT(ctrl_t *ctrl, char *arg)
{
	send_msg(ctrl->sd, "221 Goodbye.\r\n");
	uev_exit(ctrl->ctx);
}
