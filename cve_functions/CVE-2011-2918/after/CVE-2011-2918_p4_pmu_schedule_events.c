static int p4_pmu_schedule_events(struct cpu_hw_events *cpuc, int n, int *assign)
{
	unsigned long used_mask[BITS_TO_LONGS(X86_PMC_IDX_MAX)];
	unsigned long escr_mask[BITS_TO_LONGS(P4_ESCR_MSR_TABLE_SIZE)];
	int cpu = smp_processor_id();
	struct hw_perf_event *hwc;
	struct p4_event_bind *bind;
	unsigned int i, thread, num;
	int cntr_idx, escr_idx;

	bitmap_zero(used_mask, X86_PMC_IDX_MAX);
	bitmap_zero(escr_mask, P4_ESCR_MSR_TABLE_SIZE);

	for (i = 0, num = n; i < n; i++, num--) {

		hwc = &cpuc->event_list[i]->hw;
		thread = p4_ht_thread(cpu);
		bind = p4_config_get_bind(hwc->config);
		escr_idx = p4_get_escr_idx(bind->escr_msr[thread]);
		if (unlikely(escr_idx == -1))
			goto done;

		if (hwc->idx != -1 && !p4_should_swap_ts(hwc->config, cpu)) {
			cntr_idx = hwc->idx;
			if (assign)
				assign[i] = hwc->idx;
			goto reserve;
		}

		cntr_idx = p4_next_cntr(thread, used_mask, bind);
		if (cntr_idx == -1 || test_bit(escr_idx, escr_mask))
			goto done;

		p4_pmu_swap_config_ts(hwc, cpu);
		if (assign)
			assign[i] = cntr_idx;
reserve:
		set_bit(cntr_idx, used_mask);
		set_bit(escr_idx, escr_mask);
	}

done:
	return num ? -ENOSPC : 0;
}
