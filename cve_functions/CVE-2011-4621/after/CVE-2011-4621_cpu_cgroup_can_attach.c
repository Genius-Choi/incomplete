cpu_cgroup_can_attach(struct cgroup_subsys *ss, struct cgroup *cgrp,
		      struct task_struct *tsk, bool threadgroup)
{
	int retval = cpu_cgroup_can_attach_task(cgrp, tsk);
	if (retval)
		return retval;
	if (threadgroup) {
		struct task_struct *c;
		rcu_read_lock();
		list_for_each_entry_rcu(c, &tsk->thread_group, thread_group) {
			retval = cpu_cgroup_can_attach_task(cgrp, c);
			if (retval) {
				rcu_read_unlock();
				return retval;
			}
		}
		rcu_read_unlock();
	}
	return 0;
}
