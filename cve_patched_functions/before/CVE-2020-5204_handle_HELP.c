static void handle_HELP(ctrl_t *ctrl, char *arg)
{
	int i = 0;
	char buf[80];
	ftp_cmd_t *cmd;

	if (string_valid(arg) && !string_compare(arg, "SITE")) {
		send_msg(ctrl->sd, "500 command HELP does not take any arguments on this server.\r\n");
		return;
	}

	snprintf(ctrl->buf, ctrl->bufsz, "214-The following commands are recognized.");
	for (cmd = &supported[0]; cmd->command; cmd++, i++) {
		if (i % 14 == 0)
			strlcat(ctrl->buf, "\r\n", ctrl->bufsz);
		snprintf(buf, sizeof(buf), " %s", cmd->command);
		strlcat(ctrl->buf, buf, ctrl->bufsz);
	}
	snprintf(buf, sizeof(buf), "\r\n214 Help OK.\r\n");
	strlcat(ctrl->buf, buf, ctrl->bufsz);

	send_msg(ctrl->sd, ctrl->buf);
}
