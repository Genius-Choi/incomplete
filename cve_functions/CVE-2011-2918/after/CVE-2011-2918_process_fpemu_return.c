static int process_fpemu_return(int sig, void __user *fault_addr)
{
	if (sig == SIGSEGV || sig == SIGBUS) {
		struct siginfo si = {0};
		si.si_addr = fault_addr;
		si.si_signo = sig;
		if (sig == SIGSEGV) {
			if (find_vma(current->mm, (unsigned long)fault_addr))
				si.si_code = SEGV_ACCERR;
			else
				si.si_code = SEGV_MAPERR;
		} else {
			si.si_code = BUS_ADRERR;
		}
		force_sig_info(sig, &si, current);
		return 1;
	} else if (sig) {
		force_sig(sig, current);
		return 1;
	} else {
		return 0;
	}
}
