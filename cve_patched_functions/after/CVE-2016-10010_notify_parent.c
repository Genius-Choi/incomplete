notify_parent(void)
{
	if (notify_pipe[1] != -1)
		(void)write(notify_pipe[1], "", 1);
}
