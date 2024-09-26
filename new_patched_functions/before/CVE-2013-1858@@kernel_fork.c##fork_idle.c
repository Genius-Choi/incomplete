struct task_struct * __cpuinit fork_idle(int cpu)
{
	struct task_struct *task;
	task = copy_process(CLONE_VM, 0, 0, NULL, &init_struct_pid, 0);
	if (!IS_ERR(task)) {
		init_idle_pids(task->pids);
		init_idle(task, cpu);
	}

	return task;
}
