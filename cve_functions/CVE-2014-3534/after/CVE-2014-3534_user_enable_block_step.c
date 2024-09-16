void user_enable_block_step(struct task_struct *task)
{
	set_tsk_thread_flag(task, TIF_SINGLE_STEP);
	set_tsk_thread_flag(task, TIF_BLOCK_STEP);
}
