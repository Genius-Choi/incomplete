static int x86_pmu_extra_regs(u64 config, struct perf_event *event)
{
	struct extra_reg *er;

	event->hw.extra_reg = 0;
	event->hw.extra_config = 0;

	if (!x86_pmu.extra_regs)
		return 0;

	for (er = x86_pmu.extra_regs; er->msr; er++) {
		if (er->event != (config & er->config_mask))
			continue;
		if (event->attr.config1 & ~er->valid_mask)
			return -EINVAL;
		event->hw.extra_reg = er->msr;
		event->hw.extra_config = event->attr.config1;
		break;
	}
	return 0;
}
