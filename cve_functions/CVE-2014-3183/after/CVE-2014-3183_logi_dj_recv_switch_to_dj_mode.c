static int logi_dj_recv_switch_to_dj_mode(struct dj_receiver_dev *djrcv_dev,
					  unsigned timeout)
{
	struct dj_report *dj_report;
	int retval;

	dj_report = kzalloc(sizeof(struct dj_report), GFP_KERNEL);
	if (!dj_report)
		return -ENOMEM;
	dj_report->report_id = REPORT_ID_DJ_SHORT;
	dj_report->device_index = 0xFF;
	dj_report->report_type = REPORT_TYPE_CMD_SWITCH;
	dj_report->report_params[CMD_SWITCH_PARAM_DEVBITFIELD] = 0x3F;
	dj_report->report_params[CMD_SWITCH_PARAM_TIMEOUT_SECONDS] = (u8)timeout;
	retval = logi_dj_recv_send_report(djrcv_dev, dj_report);
	kfree(dj_report);

	/*
	 * Ugly sleep to work around a USB 3.0 bug when the receiver is still
	 * processing the "switch-to-dj" command while we send an other command.
	 * 50 msec should gives enough time to the receiver to be ready.
	 */
	msleep(50);

	return retval;
}
