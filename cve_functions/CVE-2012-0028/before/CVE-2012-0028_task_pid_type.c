static struct pid *task_pid_type(struct task_struct *task, enum pid_type type)
{
	struct pid *pid = NULL;
	if (type == PIDTYPE_PID)
		pid = task->pids[type].pid;
	else if (type < PIDTYPE_MAX)
		pid = task->group_leader->pids[type].pid;
	return pid;
}
