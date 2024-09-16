add_send_receive_history (char *fname)
{
	linenoiseHistoryAdd(fname);
	if (send_receive_history_file_path)
		linenoiseHistorySave(send_receive_history_file_path);
}
