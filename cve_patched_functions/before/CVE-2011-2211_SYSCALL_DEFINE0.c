SYSCALL_DEFINE0(getdtablesize)
{
	return sysctl_nr_open;
}
