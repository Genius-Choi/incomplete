notify_done(fd_set *readset)
{
	char c;

	if (notify_pipe[0] != -1 && FD_ISSET(notify_pipe[0], readset))
		while (read(notify_pipe[0], &c, 1) != -1)
			debug2("notify_done: reading");
}
