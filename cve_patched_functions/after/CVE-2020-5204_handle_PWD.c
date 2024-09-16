static void handle_PWD(ctrl_t *ctrl, char *arg)
{
	char buf[sizeof(ctrl->cwd) + 10];

	snprintf(buf, sizeof(buf), "257 \"%s\"\r\n", ctrl->cwd);
	send_msg(ctrl->sd, buf);
}
