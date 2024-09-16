static void do_unhandled_exception(int trapnr, int signr, char *str, char *fn_name,
		unsigned long error_code, struct pt_regs *regs, struct task_struct *tsk)
{
	show_excp_regs(fn_name, trapnr, signr, regs);
	tsk->thread.error_code = error_code;
	tsk->thread.trap_no = trapnr;

	if (user_mode(regs))
		force_sig(signr, tsk);

	die_if_no_fixup(str, regs, error_code);
}
