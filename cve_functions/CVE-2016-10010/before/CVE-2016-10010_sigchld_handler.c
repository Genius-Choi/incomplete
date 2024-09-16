sigchld_handler(int sig)
{
	int save_errno = errno;
	child_terminated = 1;
	signal(SIGCHLD, sigchld_handler);
	notify_parent();
	errno = save_errno;
}
