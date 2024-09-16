static inline int task_detached(struct task_struct *p)
{
	return p->exit_signal == -1;
}
