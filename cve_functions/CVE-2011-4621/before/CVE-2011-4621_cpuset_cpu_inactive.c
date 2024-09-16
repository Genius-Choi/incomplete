static int cpuset_cpu_inactive(struct notifier_block *nfb, unsigned long action,
			       void *hcpu)
{
	switch (action & ~CPU_TASKS_FROZEN) {
	case CPU_DOWN_PREPARE:
		cpuset_update_active_cpus();
		return NOTIFY_OK;
	default:
		return NOTIFY_DONE;
	}
}
