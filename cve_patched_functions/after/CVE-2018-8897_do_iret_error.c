dotraplinkage void do_iret_error(struct pt_regs *regs, long error_code)
{
	siginfo_t info;

	RCU_LOCKDEP_WARN(!rcu_is_watching(), "entry code didn't wake RCU");
	local_irq_enable();

	info.si_signo = SIGILL;
	info.si_errno = 0;
	info.si_code = ILL_BADSTK;
	info.si_addr = NULL;
	if (notify_die(DIE_TRAP, "iret exception", regs, error_code,
			X86_TRAP_IRET, SIGILL) != NOTIFY_STOP) {
		do_trap(X86_TRAP_IRET, SIGILL, "iret exception", regs, error_code,
			&info);
	}
}
