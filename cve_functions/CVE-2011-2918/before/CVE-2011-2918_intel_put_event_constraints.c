static void intel_put_event_constraints(struct cpu_hw_events *cpuc,
					struct perf_event *event)
{
	struct extra_reg *er;
	struct intel_percore *pc;
	struct er_account *era;
	struct hw_perf_event *hwc = &event->hw;
	int i, allref;

	if (!cpuc->percore_used)
		return;

	for (er = x86_pmu.extra_regs; er->msr; er++) {
		if (er->event != (hwc->config & er->config_mask))
			continue;

		pc = cpuc->per_core;
		raw_spin_lock(&pc->lock);
		for (i = 0; i < MAX_EXTRA_REGS; i++) {
			era = &pc->regs[i];
			if (era->ref > 0 &&
			    era->extra_config == hwc->extra_config &&
			    era->extra_reg == er->msr) {
				era->ref--;
				hwc->extra_alloc = 0;
				break;
			}
		}
		allref = 0;
		for (i = 0; i < MAX_EXTRA_REGS; i++)
			allref += pc->regs[i].ref;
		if (allref == 0)
			cpuc->percore_used = 0;
		raw_spin_unlock(&pc->lock);
		break;
	}
}
