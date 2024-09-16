static void __init cpu_pmu_init(struct arm_pmu *armpmu)
{
	int cpu;
	for_each_possible_cpu(cpu) {
		struct pmu_hw_events *events = &per_cpu(cpu_hw_events, cpu);
		events->events = per_cpu(hw_events, cpu);
		events->used_mask = per_cpu(used_mask, cpu);
		raw_spin_lock_init(&events->pmu_lock);
	}
	armpmu->get_hw_events = armpmu_get_cpu_events;
}
