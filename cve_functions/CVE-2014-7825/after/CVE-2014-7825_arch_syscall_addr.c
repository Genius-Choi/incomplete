unsigned long __init __weak arch_syscall_addr(int nr)
{
	return (unsigned long)sys_call_table[nr];
}
