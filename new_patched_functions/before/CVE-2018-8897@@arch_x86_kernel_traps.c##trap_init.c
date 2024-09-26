void __init trap_init(void)
{
	/* Init cpu_entry_area before IST entries are set up */
	setup_cpu_entry_areas();

	idt_setup_traps();

	/*
	 * Set the IDT descriptor to a fixed read-only location, so that the
	 * "sidt" instruction will not leak the location of the kernel, and
	 * to defend the IDT against arbitrary memory write vulnerabilities.
	 * It will be reloaded in cpu_init() */
	cea_set_pte(CPU_ENTRY_AREA_RO_IDT_VADDR, __pa_symbol(idt_table),
		    PAGE_KERNEL_RO);
	idt_descr.address = CPU_ENTRY_AREA_RO_IDT;

	/*
	 * Should be a barrier for any external CPU state:
	 */
	cpu_init();

	idt_setup_ist_traps();

	x86_init.irqs.trap_init();

	idt_setup_debugidt_traps();
}
