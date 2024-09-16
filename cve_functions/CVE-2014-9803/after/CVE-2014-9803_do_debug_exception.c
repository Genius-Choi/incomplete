asmlinkage int __exception do_debug_exception(unsigned long addr,
					      unsigned int esr,
					      struct pt_regs *regs)
{
	const struct fault_info *inf = debug_fault_info + DBG_ESR_EVT(esr);
	struct siginfo info;

	if (!inf->fn(addr, esr, regs))
		return 1;

	pr_alert("Unhandled debug exception: %s (0x%08x) at 0x%016lx\n",
		 inf->name, esr, addr);

	info.si_signo = inf->sig;
	info.si_errno = 0;
	info.si_code  = inf->code;
	info.si_addr  = (void __user *)addr;
	arm64_notify_die("", regs, &info, 0);

	return 0;
}
