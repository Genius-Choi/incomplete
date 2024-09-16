void machine_check_exception(struct pt_regs *regs)
{
	int recover = 0;
	unsigned long reason = get_mc_reason(regs);

	/* See if any machine dependent calls */
	if (ppc_md.machine_check_exception)
		recover = ppc_md.machine_check_exception(regs);

	if (recover)
		return;

	if (user_mode(regs)) {
		regs->msr |= MSR_RI;
		_exception(SIGBUS, regs, BUS_ADRERR, regs->nip);
		return;
	}

#if defined(CONFIG_8xx) && defined(CONFIG_PCI)
	/* the qspan pci read routines can cause machine checks -- Cort */
	bad_page_fault(regs, regs->dar, SIGBUS);
	return;
#endif

	if (debugger_fault_handler(regs)) {
		regs->msr |= MSR_RI;
		return;
	}

	if (check_io_access(regs))
		return;

#if defined(CONFIG_4xx) && !defined(CONFIG_440A)
	if (reason & ESR_IMCP) {
		printk("Instruction");
		mtspr(SPRN_ESR, reason & ~ESR_IMCP);
	} else
		printk("Data");
	printk(" machine check in kernel mode.\n");
#elif defined(CONFIG_440A)
	printk("Machine check in kernel mode.\n");
	if (reason & ESR_IMCP){
		printk("Instruction Synchronous Machine Check exception\n");
		mtspr(SPRN_ESR, reason & ~ESR_IMCP);
	}
	else {
		u32 mcsr = mfspr(SPRN_MCSR);
		if (mcsr & MCSR_IB)
			printk("Instruction Read PLB Error\n");
		if (mcsr & MCSR_DRB)
			printk("Data Read PLB Error\n");
		if (mcsr & MCSR_DWB)
			printk("Data Write PLB Error\n");
		if (mcsr & MCSR_TLBP)
			printk("TLB Parity Error\n");
		if (mcsr & MCSR_ICP){
			flush_instruction_cache();
			printk("I-Cache Parity Error\n");
		}
		if (mcsr & MCSR_DCSP)
			printk("D-Cache Search Parity Error\n");
		if (mcsr & MCSR_DCFP)
			printk("D-Cache Flush Parity Error\n");
		if (mcsr & MCSR_IMPE)
			printk("Machine Check exception is imprecise\n");

		/* Clear MCSR */
		mtspr(SPRN_MCSR, mcsr);
	}
#elif defined (CONFIG_E500)
	printk("Machine check in kernel mode.\n");
	printk("Caused by (from MCSR=%lx): ", reason);

	if (reason & MCSR_MCP)
		printk("Machine Check Signal\n");
	if (reason & MCSR_ICPERR)
		printk("Instruction Cache Parity Error\n");
	if (reason & MCSR_DCP_PERR)
		printk("Data Cache Push Parity Error\n");
	if (reason & MCSR_DCPERR)
		printk("Data Cache Parity Error\n");
	if (reason & MCSR_GL_CI)
		printk("Guarded Load or Cache-Inhibited stwcx.\n");
	if (reason & MCSR_BUS_IAERR)
		printk("Bus - Instruction Address Error\n");
	if (reason & MCSR_BUS_RAERR)
		printk("Bus - Read Address Error\n");
	if (reason & MCSR_BUS_WAERR)
		printk("Bus - Write Address Error\n");
	if (reason & MCSR_BUS_IBERR)
		printk("Bus - Instruction Data Error\n");
	if (reason & MCSR_BUS_RBERR)
		printk("Bus - Read Data Bus Error\n");
	if (reason & MCSR_BUS_WBERR)
		printk("Bus - Read Data Bus Error\n");
	if (reason & MCSR_BUS_IPERR)
		printk("Bus - Instruction Parity Error\n");
	if (reason & MCSR_BUS_RPERR)
		printk("Bus - Read Parity Error\n");
#elif defined (CONFIG_E200)
	printk("Machine check in kernel mode.\n");
	printk("Caused by (from MCSR=%lx): ", reason);

	if (reason & MCSR_MCP)
		printk("Machine Check Signal\n");
	if (reason & MCSR_CP_PERR)
		printk("Cache Push Parity Error\n");
	if (reason & MCSR_CPERR)
		printk("Cache Parity Error\n");
	if (reason & MCSR_EXCP_ERR)
		printk("ISI, ITLB, or Bus Error on first instruction fetch for an exception handler\n");
	if (reason & MCSR_BUS_IRERR)
		printk("Bus - Read Bus Error on instruction fetch\n");
	if (reason & MCSR_BUS_DRERR)
		printk("Bus - Read Bus Error on data load\n");
	if (reason & MCSR_BUS_WRERR)
		printk("Bus - Write Bus Error on buffered store or cache line push\n");
#else /* !CONFIG_4xx && !CONFIG_E500 && !CONFIG_E200 */
	printk("Machine check in kernel mode.\n");
	printk("Caused by (from SRR1=%lx): ", reason);
	switch (reason & 0x601F0000) {
	case 0x80000:
		printk("Machine check signal\n");
		break;
	case 0:		/* for 601 */
	case 0x40000:
	case 0x140000:	/* 7450 MSS error and TEA */
		printk("Transfer error ack signal\n");
		break;
	case 0x20000:
		printk("Data parity error signal\n");
		break;
	case 0x10000:
		printk("Address parity error signal\n");
		break;
	case 0x20000000:
		printk("L1 Data Cache error\n");
		break;
	case 0x40000000:
		printk("L1 Instruction Cache error\n");
		break;
	case 0x00100000:
		printk("L2 data cache parity error\n");
		break;
	default:
		printk("Unknown values in msr\n");
	}
#endif /* CONFIG_4xx */

	/*
	 * Optional platform-provided routine to print out
	 * additional info, e.g. bus error registers.
	 */
	platform_machine_check(regs);

	if (debugger_fault_handler(regs))
		return;
	die("Machine check", regs, SIGBUS);

	/* Must die if the interrupt is not recoverable */
	if (!(regs->msr & MSR_RI))
		panic("Unrecoverable Machine check");
}
