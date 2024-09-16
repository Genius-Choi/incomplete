asmlinkage void do_fpu_error(unsigned long r4, unsigned long r5,
			     unsigned long r6, unsigned long r7,
			     struct pt_regs regs)
{
	struct task_struct *tsk = current;
	siginfo_t info;

	if (ieee_fpe_handler (&regs))
		return;

	regs.pc += 2;
	info.si_signo = SIGFPE;
	info.si_errno = 0;
	info.si_code = FPE_FLTINV;
	info.si_addr = (void __user *)regs.pc;
	force_sig_info(SIGFPE, &info, tsk);
}
