deadly_handler(int signum)
{
	if ( ! sig_exit ) {
		sig_exit = 1;
		kill(0, SIGTERM);
	}
}
