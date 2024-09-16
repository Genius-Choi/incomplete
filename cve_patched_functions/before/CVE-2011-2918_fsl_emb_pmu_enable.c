static void fsl_emb_pmu_enable(struct pmu *pmu)
{
	struct cpu_hw_events *cpuhw;
	unsigned long flags;

	local_irq_save(flags);
	cpuhw = &__get_cpu_var(cpu_hw_events);
	if (!cpuhw->disabled)
		goto out;

	cpuhw->disabled = 0;
	ppc_set_pmu_inuse(cpuhw->n_events != 0);

	if (cpuhw->n_events > 0) {
		mtpmr(PMRN_PMGC0, PMGC0_PMIE | PMGC0_FCECE);
		isync();
	}

 out:
	local_irq_restore(flags);
}
