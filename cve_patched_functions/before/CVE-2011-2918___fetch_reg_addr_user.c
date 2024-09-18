static inline unsigned long __user *__fetch_reg_addr_user(unsigned int reg,
							  struct pt_regs *regs)
{
	BUG_ON(reg < 16);
	BUG_ON(regs->tstate & TSTATE_PRIV);

	if (test_thread_flag(TIF_32BIT)) {
		struct reg_window32 __user *win32;
		win32 = (struct reg_window32 __user *)((unsigned long)((u32)regs->u_regs[UREG_FP]));
		return (unsigned long __user *)&win32->locals[reg - 16];
	} else {
		struct reg_window __user *win;
		win = (struct reg_window __user *)(regs->u_regs[UREG_FP] + STACK_BIAS);
		return &win->locals[reg - 16];
	}
}
