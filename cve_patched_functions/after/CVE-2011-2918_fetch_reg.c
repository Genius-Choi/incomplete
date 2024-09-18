static unsigned long fetch_reg(unsigned int reg, struct pt_regs *regs)
{
	unsigned long value;
	
	if (reg < 16)
		return (!reg ? 0 : regs->u_regs[reg]);
	if (regs->tstate & TSTATE_PRIV) {
		struct reg_window *win;
		win = (struct reg_window *)(regs->u_regs[UREG_FP] + STACK_BIAS);
		value = win->locals[reg - 16];
	} else if (test_thread_flag(TIF_32BIT)) {
		struct reg_window32 __user *win32;
		win32 = (struct reg_window32 __user *)((unsigned long)((u32)regs->u_regs[UREG_FP]));
		get_user(value, &win32->locals[reg - 16]);
	} else {
		struct reg_window __user *win;
		win = (struct reg_window __user *)(regs->u_regs[UREG_FP] + STACK_BIAS);
		get_user(value, &win->locals[reg - 16]);
	}
	return value;
}
