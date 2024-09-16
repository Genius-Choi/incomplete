static void __do_fault_siginfo(int code, int sig, struct pt_regs *regs,
			       unsigned long addr)
{
	siginfo_t info;

	info.si_signo = sig;
	info.si_code = code;
	info.si_errno = 0;
	info.si_addr = (void __user *) addr;
	info.si_trapno = 0;

	if (unlikely(show_unhandled_signals))
		show_signal_msg(regs, sig, info.si_code,
				addr, current);

	force_sig_info (sig, &info, current);
}
