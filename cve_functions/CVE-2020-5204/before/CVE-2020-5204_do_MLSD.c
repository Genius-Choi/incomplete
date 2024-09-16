static void do_MLSD(ctrl_t *ctrl)
{
	char buf[512] = { 0 };

	if (list_printf(ctrl, buf, sizeof(buf), ctrl->file, basename(ctrl->file))) {
		do_abort(ctrl);
		send_msg(ctrl->sd, "550 No such file or directory.\r\n");
		return;
	}

	send_msg(ctrl->data_sd, buf);
	send_msg(ctrl->sd, "226 Transfer complete.\r\n");
}
