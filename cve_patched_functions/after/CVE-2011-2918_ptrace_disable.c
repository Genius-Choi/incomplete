void ptrace_disable(struct task_struct *child)
{
	user_disable_single_step(child);
}
