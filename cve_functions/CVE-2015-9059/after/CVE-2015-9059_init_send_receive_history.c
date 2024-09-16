init_send_receive_history (void)
{
	char *home_directory;

	home_directory = getenv("HOME");
	if (home_directory) {
		send_receive_history_file_path = 
			malloc(strlen(home_directory) + 2 + 
				   strlen(SEND_RECEIVE_HISTFILE));
		strcpy(send_receive_history_file_path, home_directory);
		if (home_directory[strlen(home_directory)-1] != '/') {
			strcat(send_receive_history_file_path, "/");
		}
		strcat(send_receive_history_file_path, SEND_RECEIVE_HISTFILE);
		linenoiseHistoryLoad(send_receive_history_file_path);
	}
}
