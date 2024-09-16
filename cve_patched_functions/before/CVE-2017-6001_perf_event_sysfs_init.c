static int __init perf_event_sysfs_init(void)
{
	struct pmu *pmu;
	int ret;

	mutex_lock(&pmus_lock);

	ret = bus_register(&pmu_bus);
	if (ret)
		goto unlock;

	list_for_each_entry(pmu, &pmus, entry) {
		if (!pmu->name || pmu->type < 0)
			continue;

		ret = pmu_dev_alloc(pmu);
		WARN(ret, "Failed to register pmu: %s, reason %d\n", pmu->name, ret);
	}
	pmu_bus_running = 1;
	ret = 0;

unlock:
	mutex_unlock(&pmus_lock);

	return ret;
}
