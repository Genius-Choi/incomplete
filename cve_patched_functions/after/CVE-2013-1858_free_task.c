void free_task(struct task_struct *tsk)
{
	account_kernel_stack(tsk->stack, -1);
	arch_release_thread_info(tsk->stack);
	free_thread_info(tsk->stack);
	rt_mutex_debug_task_free(tsk);
	ftrace_graph_exit_task(tsk);
	put_seccomp_filter(tsk);
	arch_release_task_struct(tsk);
	free_task_struct(tsk);
}
