notify_fifo(vector_t *strvec, const char *type, notify_fifo_t *fifo)
{
	if (vector_size(strvec) < 2) {
		report_config_error(CONFIG_GENERAL_ERROR, "No %snotify_fifo name specified", type);
		return;
	}

	if (fifo->name) {
		report_config_error(CONFIG_GENERAL_ERROR, "%snotify_fifo already specified - ignoring %s", type, FMT_STR_VSLOT(strvec,1));
		return;
	}

	fifo->name = MALLOC(strlen(strvec_slot(strvec, 1)) + 1);
	strcpy(fifo->name, strvec_slot(strvec, 1));
}
