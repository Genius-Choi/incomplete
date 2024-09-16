void show_regs(struct pt_regs * regs)
{
	printk("\n");
	__show_regs(regs);
	dump_stack();
}
