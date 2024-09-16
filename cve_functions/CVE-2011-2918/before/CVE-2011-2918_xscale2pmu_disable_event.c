xscale2pmu_disable_event(struct hw_perf_event *hwc, int idx)
{
	unsigned long flags, ien, evtsel;

	ien = xscale2pmu_read_int_enable();
	evtsel = xscale2pmu_read_event_select();

	switch (idx) {
	case XSCALE_CYCLE_COUNTER:
		ien &= ~XSCALE2_CCOUNT_INT_EN;
		break;
	case XSCALE_COUNTER0:
		ien &= ~XSCALE2_COUNT0_INT_EN;
		evtsel &= ~XSCALE2_COUNT0_EVT_MASK;
		evtsel |= XSCALE_PERFCTR_UNUSED << XSCALE2_COUNT0_EVT_SHFT;
		break;
	case XSCALE_COUNTER1:
		ien &= ~XSCALE2_COUNT1_INT_EN;
		evtsel &= ~XSCALE2_COUNT1_EVT_MASK;
		evtsel |= XSCALE_PERFCTR_UNUSED << XSCALE2_COUNT1_EVT_SHFT;
		break;
	case XSCALE_COUNTER2:
		ien &= ~XSCALE2_COUNT2_INT_EN;
		evtsel &= ~XSCALE2_COUNT2_EVT_MASK;
		evtsel |= XSCALE_PERFCTR_UNUSED << XSCALE2_COUNT2_EVT_SHFT;
		break;
	case XSCALE_COUNTER3:
		ien &= ~XSCALE2_COUNT3_INT_EN;
		evtsel &= ~XSCALE2_COUNT3_EVT_MASK;
		evtsel |= XSCALE_PERFCTR_UNUSED << XSCALE2_COUNT3_EVT_SHFT;
		break;
	default:
		WARN_ONCE(1, "invalid counter number (%d)\n", idx);
		return;
	}

	raw_spin_lock_irqsave(&pmu_lock, flags);
	xscale2pmu_write_event_select(evtsel);
	xscale2pmu_write_int_enable(ien);
	raw_spin_unlock_irqrestore(&pmu_lock, flags);
}
