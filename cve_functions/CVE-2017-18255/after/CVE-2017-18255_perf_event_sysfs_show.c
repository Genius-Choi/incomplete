ssize_t perf_event_sysfs_show(struct device *dev, struct device_attribute *attr,
			      char *page)
{
	struct perf_pmu_events_attr *pmu_attr =
		container_of(attr, struct perf_pmu_events_attr, attr);

	if (pmu_attr->event_str)
		return sprintf(page, "%s\n", pmu_attr->event_str);

	return 0;
}
