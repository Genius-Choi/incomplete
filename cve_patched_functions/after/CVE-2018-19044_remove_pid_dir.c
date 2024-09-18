remove_pid_dir(void)
{
	if (rmdir(pid_directory) && errno != ENOTEMPTY && errno != EBUSY)
		log_message(LOG_INFO, "unlink of %s failed - error (%d) '%s'", pid_directory, errno, strerror(errno));
}
