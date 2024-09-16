static int has_stopped_jobs(struct pid *pgrp)
{
	int retval = 0;
	struct task_struct *p;

	do_each_pid_task(pgrp, PIDTYPE_PGID, p) {
		if (!task_is_stopped(p))
			continue;
		retval = 1;
		break;
	} while_each_pid_task(pgrp, PIDTYPE_PGID, p);
	return retval;
}
