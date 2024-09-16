static void perf_cgroup_attach(struct cgroup_subsys_state *css,
			       struct cgroup_taskset *tset)
{
	struct task_struct *task;

	cgroup_taskset_for_each(task, tset)
		task_function_call(task, __perf_cgroup_move, task);
}
