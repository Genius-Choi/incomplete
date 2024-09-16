static inline void clear_AC(struct kernel_vm86_regs *regs)
{
	regs->pt.flags &= ~X86_EFLAGS_AC;
}
