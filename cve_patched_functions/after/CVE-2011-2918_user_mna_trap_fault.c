static void user_mna_trap_fault(struct pt_regs *regs, unsigned int insn)
{
	siginfo_t info;

	info.si_signo = SIGBUS;
	info.si_errno = 0;
	info.si_code = BUS_ADRALN;
	info.si_addr = (void __user *)safe_compute_effective_address(regs, insn);
	info.si_trapno = 0;
	send_sig_info(SIGBUS, &info, current);
}
