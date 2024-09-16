static void __kprobes bad_kernel_pc(struct pt_regs *regs, unsigned long vaddr)
{
	printk(KERN_CRIT "OOPS: Bogus kernel PC [%016lx] in fault handler\n",
	       regs->tpc);
	printk(KERN_CRIT "OOPS: RPC [%016lx]\n", regs->u_regs[15]);
	printk("OOPS: RPC <%pS>\n", (void *) regs->u_regs[15]);
	printk(KERN_CRIT "OOPS: Fault was to vaddr[%lx]\n", vaddr);
	dump_stack();
	unhandled_fault(regs->tpc, current, regs);
}
