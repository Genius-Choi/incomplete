int generic_ptrace_pokedata(struct task_struct *tsk, unsigned long addr,
			    unsigned long data)
{
	int copied;

	copied = ptrace_access_vm(tsk, addr, &data, sizeof(data),
			FOLL_FORCE | FOLL_WRITE);
	return (copied == sizeof(data)) ? 0 : -EIO;
}
