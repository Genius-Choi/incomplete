int cap_task_setioprio(struct task_struct *p, int ioprio)
{
	return cap_safe_nice(p);
}
