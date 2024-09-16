void user_single_step_siginfo(struct task_struct *tsk,
				struct pt_regs *regs,
				struct siginfo *info)
{
	fill_sigtrap_info(tsk, regs, 0, TRAP_BRKPT, info);
}
