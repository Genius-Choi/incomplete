NORET_TYPE void ATTRIB_NORET nmi_exception_handler(struct pt_regs *regs)
{
	bust_spinlocks(1);
	printk("NMI taken!!!!\n");
	die("NMI", regs);
}
