void perf_cpu_hrtimer_cancel(int cpu)
{
	struct perf_cpu_context *cpuctx;
	struct pmu *pmu;
	unsigned long flags;

	if (WARN_ON(cpu != smp_processor_id()))
		return;

	local_irq_save(flags);

	rcu_read_lock();

	list_for_each_entry_rcu(pmu, &pmus, entry) {
		cpuctx = this_cpu_ptr(pmu->pmu_cpu_context);

		if (pmu->task_ctx_nr == perf_sw_context)
			continue;

		hrtimer_cancel(&cpuctx->hrtimer);
	}

	rcu_read_unlock();

	local_irq_restore(flags);
}
