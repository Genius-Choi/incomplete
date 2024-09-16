static void ftp_command(ctrl_t *ctrl)
{
	uev_t sigterm_watcher;

	ctrl->bufsz = BUFFER_SIZE * sizeof(char);
	ctrl->buf   = malloc(ctrl->bufsz);
	if (!ctrl->buf) {
                WARN(errno, "FTP session failed allocating buffer");
                exit(1);
	}

	snprintf(ctrl->buf, ctrl->bufsz, "220 %s (%s) ready.\r\n", prognm, VERSION);
	send_msg(ctrl->sd, ctrl->buf);

	uev_signal_init(ctrl->ctx, &sigterm_watcher, child_exit, NULL, SIGTERM);
	uev_io_init(ctrl->ctx, &ctrl->io_watcher, read_client_command, ctrl, ctrl->sd, UEV_READ);
	uev_run(ctrl->ctx, 0);
}
