static void intel_pmu_cpu_dying(int cpu)
{
	struct cpu_hw_events *cpuc = &per_cpu(cpu_hw_events, cpu);
	struct intel_percore *pc = cpuc->per_core;

	if (pc) {
		if (pc->core_id == -1 || --pc->refcnt == 0)
			kfree(pc);
		cpuc->per_core = NULL;
	}

	fini_debug_store_on_cpu(cpu);
}
