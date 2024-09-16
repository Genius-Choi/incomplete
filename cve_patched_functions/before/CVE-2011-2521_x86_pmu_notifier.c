x86_pmu_notifier(struct notifier_block *self, unsigned long action, void *hcpu)
{
	unsigned int cpu = (long)hcpu;
	int ret = NOTIFY_OK;

	switch (action & ~CPU_TASKS_FROZEN) {
	case CPU_UP_PREPARE:
		if (x86_pmu.cpu_prepare)
			ret = x86_pmu.cpu_prepare(cpu);
		break;

	case CPU_STARTING:
		if (x86_pmu.cpu_starting)
			x86_pmu.cpu_starting(cpu);
		break;

	case CPU_DYING:
		if (x86_pmu.cpu_dying)
			x86_pmu.cpu_dying(cpu);
		break;

	case CPU_UP_CANCELED:
	case CPU_DEAD:
		if (x86_pmu.cpu_dead)
			x86_pmu.cpu_dead(cpu);
		break;

	default:
		break;
	}

	return ret;
}
