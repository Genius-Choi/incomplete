int do_unknown_trapa(unsigned long scId, struct pt_regs *regs)
{
	/* Syscall debug */
        printk("System call ID error: [0x1#args:8 #syscall:16  0x%lx]\n", scId);

	die_if_kernel("unknown trapa", regs, scId);

	return -ENOSYS;
}
