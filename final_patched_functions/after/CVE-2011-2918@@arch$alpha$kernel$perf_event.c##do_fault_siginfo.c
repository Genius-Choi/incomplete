static noinline void do_fault_siginfo(int code, int sig, struct pt_regs *regs,
				      int text_fault)
{
	unsigned long addr = compute_si_addr(regs, text_fault);

	__do_fault_siginfo(code, sig, regs, addr);
}
