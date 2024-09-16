perf_event_mux_interval_ms_show(struct device *dev,
				struct device_attribute *attr,
				char *page)
{
	struct pmu *pmu = dev_get_drvdata(dev);

	return snprintf(page, PAGE_SIZE-1, "%d\n", pmu->hrtimer_interval_ms);
}
