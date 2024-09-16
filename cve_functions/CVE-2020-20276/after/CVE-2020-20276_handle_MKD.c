static void handle_MKD(ctrl_t *ctrl, char *arg)
{
	char *path;

	path = compose_abspath(ctrl, arg);
	if (!path) {
		INFO("Invalid path for %s: %m", arg);
		goto fail;
	}

	if (mkdir(path, 0755)) {
		if (EPERM == errno)
		fail:	send_msg(ctrl->sd, "550 Not allowed to create directory.\r\n");
		else
			send_msg(ctrl->sd, "550 Unknown error.\r\n");
		return;
	}

	send_msg(ctrl->sd, "200 Command OK\r\n");
}
