static inline void __x86_pmu_enable_event(struct hw_perf_event *hwc,
					  u64 enable_mask)
{
	if (hwc->extra_reg)
		wrmsrl(hwc->extra_reg, hwc->extra_config);
	wrmsrl(hwc->config_base, hwc->config | enable_mask);
}
