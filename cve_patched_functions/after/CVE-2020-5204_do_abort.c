static int do_abort(ctrl_t *ctrl)
{
	if (ctrl->d || ctrl->d_num) {
		uev_io_stop(&ctrl->data_watcher);
		if (ctrl->d_num > 0)
			free(ctrl->d);
		ctrl->d_num = 0;
		ctrl->d = NULL;
		ctrl->i = 0;

		if (ctrl->file)
			free(ctrl->file);
		ctrl->file = NULL;
	}

	if (ctrl->file) {
		uev_io_stop(&ctrl->data_watcher);
		free(ctrl->file);
		ctrl->file = NULL;
	}

	if (ctrl->fp) {
		fclose(ctrl->fp);
		ctrl->fp = NULL;
	}

	ctrl->pending = 0;
	ctrl->offset = 0;

	return close_data_connection(ctrl);
}
