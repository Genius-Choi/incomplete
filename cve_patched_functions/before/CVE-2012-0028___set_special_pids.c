void __set_special_pids(struct pid *pid)
{
	struct task_struct *curr = current->group_leader;
	pid_t nr = pid_nr(pid);

	if (task_session(curr) != pid) {
		change_pid(curr, PIDTYPE_SID, pid);
		set_task_session(curr, nr);
	}
	if (task_pgrp(curr) != pid) {
		change_pid(curr, PIDTYPE_PGID, pid);
		set_task_pgrp(curr, nr);
	}
}
