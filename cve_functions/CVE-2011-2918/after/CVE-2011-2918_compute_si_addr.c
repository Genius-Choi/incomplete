static unsigned long compute_si_addr(struct pt_regs *regs, int text_fault)
{
	unsigned int insn;

	if (text_fault)
		return regs->pc;

	if (regs->psr & PSR_PS) {
		insn = *(unsigned int *) regs->pc;
	} else {
		__get_user(insn, (unsigned int *) regs->pc);
	}

	return safe_compute_effective_address(regs, insn);
}
