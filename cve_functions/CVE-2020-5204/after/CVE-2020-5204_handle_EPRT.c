static void handle_EPRT(ctrl_t *ctrl, char *str)
{
	send_msg(ctrl->sd, "502 Command not implemented.\r\n");
}
