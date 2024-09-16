static int break_trap(struct pt_regs *regs, unsigned int instr)
{
	ptrace_break(current, regs);
	return 0;
}
