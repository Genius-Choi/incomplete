cpu_cgroup_attach(struct cgroup_subsys *ss, struct cgroup *cgrp,
		  struct cgroup *old_cont, struct task_struct *tsk,
		  bool threadgroup)
{
	sched_move_task(tsk);
	if (threadgroup) {
		struct task_struct *c;
		rcu_read_lock();
		list_for_each_entry_rcu(c, &tsk->thread_group, thread_group) {
			sched_move_task(c);
		}
		rcu_read_unlock();
	}
}
