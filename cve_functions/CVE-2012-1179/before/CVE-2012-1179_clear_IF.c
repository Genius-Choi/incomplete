static inline void clear_IF(struct kernel_vm86_regs *regs)
{
	VEFLAGS &= ~X86_EFLAGS_VIF;
}
