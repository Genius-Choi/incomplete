pidfile_rm(const char *pid_file)
{
	unlink(pid_file);
}
