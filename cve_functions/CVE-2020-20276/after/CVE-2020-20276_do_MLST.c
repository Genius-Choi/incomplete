static void do_MLST(ctrl_t *ctrl)
{
	size_t len = 0;
	char buf[512] = { 0 };
	int sd = ctrl->sd;

	if (ctrl->data_sd != -1)
		sd = ctrl->data_sd;

	snprintf(buf, sizeof(buf), "250- Listing %s\r\n", ctrl->file);
	len = strlen(buf);

	if (list_printf(ctrl, &buf[len], sizeof(buf) -  len, ctrl->file, basename(ctrl->file))) {
		do_abort(ctrl);
		send_msg(ctrl->sd, "550 No such file or directory.\r\n");
		return;
	}

	strlcat(buf, "250 End.\r\n", sizeof(buf));
	send_msg(sd, buf);
}
