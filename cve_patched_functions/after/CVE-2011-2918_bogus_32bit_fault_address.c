static void noinline __kprobes bogus_32bit_fault_address(struct pt_regs *regs,
							 unsigned long addr)
{
	static int times;

	if (times++ < 10)
		printk(KERN_ERR "FAULT[%s:%d]: 32-bit process "
		       "reports 64-bit fault address [%lx]\n",
		       current->comm, current->pid, addr);
	show_regs(regs);
}
