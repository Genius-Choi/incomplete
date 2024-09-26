void perf_event_print_debug(void)
{
	u64 ctrl, status, overflow, pmc_ctrl, pmc_count, prev_left, fixed;
	u64 pebs;
	struct cpu_hw_events *cpuc;
	unsigned long flags;
	int cpu, idx;

	if (!x86_pmu.num_counters)
		return;

	local_irq_save(flags);

	cpu = smp_processor_id();
	cpuc = &per_cpu(cpu_hw_events, cpu);

	if (x86_pmu.version >= 2) {
		rdmsrl(MSR_CORE_PERF_GLOBAL_CTRL, ctrl);
		rdmsrl(MSR_CORE_PERF_GLOBAL_STATUS, status);
		rdmsrl(MSR_CORE_PERF_GLOBAL_OVF_CTRL, overflow);
		rdmsrl(MSR_ARCH_PERFMON_FIXED_CTR_CTRL, fixed);
		rdmsrl(MSR_IA32_PEBS_ENABLE, pebs);

		pr_info("\n");
		pr_info("CPU#%d: ctrl:       %016llx\n", cpu, ctrl);
		pr_info("CPU#%d: status:     %016llx\n", cpu, status);
		pr_info("CPU#%d: overflow:   %016llx\n", cpu, overflow);
		pr_info("CPU#%d: fixed:      %016llx\n", cpu, fixed);
		pr_info("CPU#%d: pebs:       %016llx\n", cpu, pebs);
	}
	pr_info("CPU#%d: active:     %016llx\n", cpu, *(u64 *)cpuc->active_mask);

	for (idx = 0; idx < x86_pmu.num_counters; idx++) {
		rdmsrl(x86_pmu_config_addr(idx), pmc_ctrl);
		rdmsrl(x86_pmu_event_addr(idx), pmc_count);

		prev_left = per_cpu(pmc_prev_left[idx], cpu);

		pr_info("CPU#%d:   gen-PMC%d ctrl:  %016llx\n",
			cpu, idx, pmc_ctrl);
		pr_info("CPU#%d:   gen-PMC%d count: %016llx\n",
			cpu, idx, pmc_count);
		pr_info("CPU#%d:   gen-PMC%d left:  %016llx\n",
			cpu, idx, prev_left);
	}
	for (idx = 0; idx < x86_pmu.num_counters_fixed; idx++) {
		rdmsrl(MSR_ARCH_PERFMON_FIXED_CTR0 + idx, pmc_count);

		pr_info("CPU#%d: fixed-PMC%d count: %016llx\n",
			cpu, idx, pmc_count);
	}
	local_irq_restore(flags);
}
