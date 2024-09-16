asmlinkage void sparc_lvl15_nmi(struct pt_regs *regs, unsigned long serr,
				unsigned long svaddr, unsigned long aerr,
				unsigned long avaddr)
{
	sun4c_complete_all_stores();
	printk("FAULT: NMI received\n");
	printk("SREGS: Synchronous Error %08lx\n", serr);
	printk("       Synchronous Vaddr %08lx\n", svaddr);
	printk("      Asynchronous Error %08lx\n", aerr);
	printk("      Asynchronous Vaddr %08lx\n", avaddr);
	if (sun4c_memerr_reg)
		printk("     Memory Parity Error %08lx\n", *sun4c_memerr_reg);
	printk("REGISTER DUMP:\n");
	show_regs(regs);
	prom_halt();
}
