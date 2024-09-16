perf_cpu_notify(struct notifier_block *self, unsigned long action, void *hcpu)
{
	unsigned int cpu = (long)hcpu;

	switch (action & ~CPU_TASKS_FROZEN) {

	case CPU_UP_PREPARE:
	case CPU_DOWN_FAILED:
		perf_event_init_cpu(cpu);
		break;

	case CPU_UP_CANCELED:
	case CPU_DOWN_PREPARE:
		perf_event_exit_cpu(cpu);
		break;
	default:
		break;
	}

	return NOTIFY_OK;
}
