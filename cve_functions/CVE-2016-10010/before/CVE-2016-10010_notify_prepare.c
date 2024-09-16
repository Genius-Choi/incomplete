notify_prepare(fd_set *readset)
{
	if (notify_pipe[0] != -1)
		FD_SET(notify_pipe[0], readset);
}
