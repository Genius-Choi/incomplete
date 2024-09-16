perf_event_mux_interval_ms_store(struct device *dev,
				 struct device_attribute *attr,
				 const char *buf, size_t count)
{
	struct pmu *pmu = dev_get_drvdata(dev);
	int timer, cpu, ret;

	ret = kstrtoint(buf, 0, &timer);
	if (ret)
		return ret;

	if (timer < 1)
		return -EINVAL;

	/* same value, noting to do */
	if (timer == pmu->hrtimer_interval_ms)
		return count;

	pmu->hrtimer_interval_ms = timer;

	/* update all cpuctx for this PMU */
	for_each_possible_cpu(cpu) {
		struct perf_cpu_context *cpuctx;
		cpuctx = per_cpu_ptr(pmu->pmu_cpu_context, cpu);
		cpuctx->hrtimer_interval = ns_to_ktime(NSEC_PER_MSEC * timer);

		if (hrtimer_active(&cpuctx->hrtimer))
			hrtimer_forward_now(&cpuctx->hrtimer, cpuctx->hrtimer_interval);
	}

	return count;
}
