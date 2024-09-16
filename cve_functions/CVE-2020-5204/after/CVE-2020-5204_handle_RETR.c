static void handle_RETR(ctrl_t *ctrl, char *file)
{
	FILE *fp;
	char *path;
	struct stat st;

	path = compose_abspath(ctrl, file);
	if (!path || stat(path, &st) || !S_ISREG(st.st_mode)) {
		send_msg(ctrl->sd, "550 Not a regular file.\r\n");
		return;
	}

	fp = fopen(path, "rb");
	if (!fp) {
		if (errno != ENOENT)
			ERR(errno, "Failed RETR %s for %s", path, ctrl->clientaddr);
		send_msg(ctrl->sd, "451 Trouble to RETR file.\r\n");
		return;
	}

	ctrl->fp = fp;
	ctrl->file = strdup(file);

	if (ctrl->data_sd > -1) {
		if (ctrl->offset) {
			DBG("Previous REST %ld of file size %ld", ctrl->offset, st.st_size);
			if (fseek(fp, ctrl->offset, SEEK_SET)) {
				do_abort(ctrl);
				send_msg(ctrl->sd, "551 Failed seeking to that position in file.\r\n");
				return;
			}
		}

		send_msg(ctrl->sd, "125 Data connection already open; transfer starting.\r\n");
		uev_io_init(ctrl->ctx, &ctrl->data_watcher, do_RETR, ctrl, ctrl->data_sd, UEV_WRITE);
		return;
	}

	do_PORT(ctrl, 2);
}
