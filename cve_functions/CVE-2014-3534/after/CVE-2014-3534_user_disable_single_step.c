void user_disable_single_step(struct task_struct *task)
{
	clear_tsk_thread_flag(task, TIF_BLOCK_STEP);
	clear_tsk_thread_flag(task, TIF_SINGLE_STEP);
}
