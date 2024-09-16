perf_reboot(struct notifier_block *notifier, unsigned long val, void *v)
{
	int cpu;

	for_each_online_cpu(cpu)
		perf_event_exit_cpu(cpu);

	return NOTIFY_OK;
}
