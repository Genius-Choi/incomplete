static inline void set_vflags_long(unsigned long flags, struct kernel_vm86_regs *regs)
{
	set_flags(VEFLAGS, flags, current->thread.v86mask);
	set_flags(regs->pt.flags, flags, SAFE_MASK);
	if (flags & X86_EFLAGS_IF)
		set_IF(regs);
	else
		clear_IF(regs);
}
