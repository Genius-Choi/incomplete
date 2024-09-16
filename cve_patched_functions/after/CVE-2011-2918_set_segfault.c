static void set_segfault(struct pt_regs *regs, unsigned long addr)
{
	siginfo_t info;

	if (find_vma(current->mm, addr) == NULL)
		info.si_code = SEGV_MAPERR;
	else
		info.si_code = SEGV_ACCERR;

	info.si_signo = SIGSEGV;
	info.si_errno = 0;
	info.si_addr  = (void *) instruction_pointer(regs);

	pr_debug("SWP{B} emulation: access caused memory abort!\n");
	arm_notify_die("Illegal memory access", regs, &info, 0, 0);

	abtcounter++;
}
