static void handle_REST(ctrl_t *ctrl, char *arg)
{
	const char *errstr;
	char buf[80];

	if (!string_valid(arg)) {
		send_msg(ctrl->sd, "550 Invalid argument.\r\n");
		return;
	}

	ctrl->offset = strtonum(arg, 0, INT64_MAX, &errstr);
	snprintf(buf, sizeof(buf), "350 Restarting at %ld.  Send STOR or RETR to continue transfer.\r\n", ctrl->offset);
	send_msg(ctrl->sd, buf);
}
