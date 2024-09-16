static void perf_pmu_sched_task(struct task_struct *prev,
				struct task_struct *next,
				bool sched_in)
{
	struct perf_cpu_context *cpuctx;
	struct pmu *pmu;
	unsigned long flags;

	if (prev == next)
		return;

	local_irq_save(flags);

	rcu_read_lock();

	list_for_each_entry_rcu(pmu, &pmus, entry) {
		if (pmu->sched_task) {
			cpuctx = this_cpu_ptr(pmu->pmu_cpu_context);

			perf_ctx_lock(cpuctx, cpuctx->task_ctx);

			perf_pmu_disable(pmu);

			pmu->sched_task(cpuctx->task_ctx, sched_in);

			perf_pmu_enable(pmu);

			perf_ctx_unlock(cpuctx, cpuctx->task_ctx);
		}
	}

	rcu_read_unlock();

	local_irq_restore(flags);
}
