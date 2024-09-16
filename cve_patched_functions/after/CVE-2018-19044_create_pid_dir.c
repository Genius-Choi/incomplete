create_pid_dir(void)
{
	if (mkdir(pid_directory, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) && errno != EEXIST) {
		log_message(LOG_INFO, "Unable to create directory %s", pid_directory);
		return;
	}
}
