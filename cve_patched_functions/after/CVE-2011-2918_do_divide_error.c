asmlinkage void do_divide_error(unsigned long r4, unsigned long r5,
				unsigned long r6, unsigned long r7,
				struct pt_regs __regs)
{
	siginfo_t info;

	switch (r4) {
	case TRAP_DIVZERO_ERROR:
		info.si_code = FPE_INTDIV;
		break;
	case TRAP_DIVOVF_ERROR:
		info.si_code = FPE_INTOVF;
		break;
	}

	force_sig_info(SIGFPE, &info, current);
}
