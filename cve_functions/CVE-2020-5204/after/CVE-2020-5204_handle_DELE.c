static void handle_DELE(ctrl_t *ctrl, char *file)
{
	char *path;

	path = compose_abspath(ctrl, file);
	if (!path) {
		ERR(errno, "Cannot find %s", file);
		goto fail;
	}

	if (remove(path)) {
		if (ENOENT == errno)
		fail:	send_msg(ctrl->sd, "550 No such file or directory.\r\n");
		else if (EPERM == errno)
			send_msg(ctrl->sd, "550 Not allowed to remove file or directory.\r\n");
		else
			send_msg(ctrl->sd, "550 Unknown error.\r\n");
		return;
	}

	send_msg(ctrl->sd, "200 Command OK\r\n");
}
