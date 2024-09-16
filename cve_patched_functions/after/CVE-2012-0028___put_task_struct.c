void __put_task_struct(struct task_struct *tsk)
{
	WARN_ON(!tsk->exit_state);
	WARN_ON(atomic_read(&tsk->usage));
	WARN_ON(tsk == current);

	security_task_free(tsk);
	free_uid(tsk->user);
	put_group_info(tsk->group_info);
	delayacct_tsk_free(tsk);

	if (!profile_handoff_task(tsk))
		free_task(tsk);
}
