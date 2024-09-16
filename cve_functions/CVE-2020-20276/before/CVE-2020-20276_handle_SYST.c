static void handle_SYST(ctrl_t *ctrl, char *arg)
{
	char system[] = "215 UNIX Type: L8\r\n";

	send_msg(ctrl->sd, system);
}
