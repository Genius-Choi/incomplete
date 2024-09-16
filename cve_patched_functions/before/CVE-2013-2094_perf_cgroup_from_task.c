perf_cgroup_from_task(struct task_struct *task)
{
	return container_of(task_subsys_state(task, perf_subsys_id),
			struct perf_cgroup, css);
}
