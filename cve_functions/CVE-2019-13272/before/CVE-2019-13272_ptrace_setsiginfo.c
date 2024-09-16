static int ptrace_setsiginfo(struct task_struct *child, const kernel_siginfo_t *info)
{
	unsigned long flags;
	int error = -ESRCH;

	if (lock_task_sighand(child, &flags)) {
		error = -EINVAL;
		if (likely(child->last_siginfo != NULL)) {
			copy_siginfo(child->last_siginfo, info);
			error = 0;
		}
		unlock_task_sighand(child, &flags);
	}
	return error;
}
