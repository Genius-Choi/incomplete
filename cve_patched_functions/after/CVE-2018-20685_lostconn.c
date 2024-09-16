lostconn(int signo)
{
	if (!iamremote)
		(void)write(STDERR_FILENO, "lost connection\n", 16);
	if (signo)
		_exit(1);
	else
		exit(1);
}
