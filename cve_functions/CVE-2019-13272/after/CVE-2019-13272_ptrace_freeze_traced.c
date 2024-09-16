static bool ptrace_freeze_traced(struct task_struct *task)
{
	bool ret = false;

	/* Lockless, nobody but us can set this flag */
	if (task->jobctl & JOBCTL_LISTENING)
		return ret;

	spin_lock_irq(&task->sighand->siglock);
	if (task_is_traced(task) && !__fatal_signal_pending(task)) {
		task->state = __TASK_TRACED;
		ret = true;
	}
	spin_unlock_irq(&task->sighand->siglock);

	return ret;
}
