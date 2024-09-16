SYSCALL_DEFINE0(vfork)
{
	return do_fork(CLONE_VFORK | CLONE_VM | SIGCHLD, 0, 
			0, NULL, NULL);
}
