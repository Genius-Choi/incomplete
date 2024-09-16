static int __perf_cgroup_move(void *info)
{
	struct task_struct *task = info;
	perf_cgroup_switch(task, PERF_CGROUP_SWOUT | PERF_CGROUP_SWIN);
	return 0;
}
