static int intel_pmu_cpu_prepare(int cpu)
{
	struct cpu_hw_events *cpuc = &per_cpu(cpu_hw_events, cpu);

	if (!cpu_has_ht_siblings())
		return NOTIFY_OK;

	cpuc->per_core = kzalloc_node(sizeof(struct intel_percore),
				      GFP_KERNEL, cpu_to_node(cpu));
	if (!cpuc->per_core)
		return NOTIFY_BAD;

	raw_spin_lock_init(&cpuc->per_core->lock);
	cpuc->per_core->core_id = -1;
	return NOTIFY_OK;
}
