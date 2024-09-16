u64 perf_swevent_set_period(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	u64 period = hwc->last_period;
	u64 nr, offset;
	s64 old, val;

	hwc->last_period = hwc->sample_period;

again:
	old = val = local64_read(&hwc->period_left);
	if (val < 0)
		return 0;

	nr = div64_u64(period + val, period);
	offset = nr * period;
	val -= offset;
	if (local64_cmpxchg(&hwc->period_left, old, val) != old)
		goto again;

	return nr;
}
