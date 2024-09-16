static void handle_CLNT(ctrl_t *ctrl, char *arg)
{
	send_msg(ctrl->sd, "200 CLNT\r\n");
}
