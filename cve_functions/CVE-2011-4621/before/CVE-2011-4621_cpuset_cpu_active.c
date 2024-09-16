static int cpuset_cpu_active(struct notifier_block *nfb, unsigned long action,
			     void *hcpu)
{
	switch (action & ~CPU_TASKS_FROZEN) {
	case CPU_ONLINE:
	case CPU_DOWN_FAILED:
		cpuset_update_active_cpus();
		return NOTIFY_OK;
	default:
		return NOTIFY_DONE;
	}
}
