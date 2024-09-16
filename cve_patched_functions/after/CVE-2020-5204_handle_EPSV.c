static void handle_EPSV(ctrl_t *ctrl, char *arg)
{
	struct sockaddr_in data;
	socklen_t len = sizeof(data);
	char buf[200];

	if (string_valid(arg) && string_case_compare(arg, "ALL")) {
		send_msg(ctrl->sd, "200 Command OK\r\n");
		return;
	}

	if (do_PASV(ctrl, arg, (struct sockaddr *)&data, &len))
		return;

	snprintf(buf, sizeof(buf), "229 Entering Extended Passive Mode (|||%d|)\r\n", ntohs(data.sin_port));
	send_msg(ctrl->sd, buf);
}
