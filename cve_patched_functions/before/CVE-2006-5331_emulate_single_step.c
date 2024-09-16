static void emulate_single_step(struct pt_regs *regs)
{
	if (single_stepping(regs)) {
		clear_single_step(regs);
		_exception(SIGTRAP, regs, TRAP_TRACE, 0);
	}
}
