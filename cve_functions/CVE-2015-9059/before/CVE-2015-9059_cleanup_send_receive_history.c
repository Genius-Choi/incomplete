cleanup_send_receive_history (void)
{
	if (send_receive_history_file_path)
		free(send_receive_history_file_path);
}
