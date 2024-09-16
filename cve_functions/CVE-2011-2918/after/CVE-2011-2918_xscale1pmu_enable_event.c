xscale1pmu_enable_event(struct hw_perf_event *hwc, int idx)
{
	unsigned long val, mask, evt, flags;

	switch (idx) {
	case XSCALE_CYCLE_COUNTER:
		mask = 0;
		evt = XSCALE1_CCOUNT_INT_EN;
		break;
	case XSCALE_COUNTER0:
		mask = XSCALE1_COUNT0_EVT_MASK;
		evt = (hwc->config_base << XSCALE1_COUNT0_EVT_SHFT) |
			XSCALE1_COUNT0_INT_EN;
		break;
	case XSCALE_COUNTER1:
		mask = XSCALE1_COUNT1_EVT_MASK;
		evt = (hwc->config_base << XSCALE1_COUNT1_EVT_SHFT) |
			XSCALE1_COUNT1_INT_EN;
		break;
	default:
		WARN_ONCE(1, "invalid counter number (%d)\n", idx);
		return;
	}

	raw_spin_lock_irqsave(&pmu_lock, flags);
	val = xscale1pmu_read_pmnc();
	val &= ~mask;
	val |= evt;
	xscale1pmu_write_pmnc(val);
	raw_spin_unlock_irqrestore(&pmu_lock, flags);
}
