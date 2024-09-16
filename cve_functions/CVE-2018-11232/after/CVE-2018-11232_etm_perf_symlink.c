int etm_perf_symlink(struct coresight_device *csdev, bool link)
{
	char entry[sizeof("cpu9999999")];
	int ret = 0, cpu = source_ops(csdev)->cpu_id(csdev);
	struct device *pmu_dev = etm_pmu.dev;
	struct device *cs_dev = &csdev->dev;

	sprintf(entry, "cpu%d", cpu);

	if (!etm_perf_up)
		return -EPROBE_DEFER;

	if (link) {
		ret = sysfs_create_link(&pmu_dev->kobj, &cs_dev->kobj, entry);
		if (ret)
			return ret;
		per_cpu(csdev_src, cpu) = csdev;
	} else {
		sysfs_remove_link(&pmu_dev->kobj, entry);
		per_cpu(csdev_src, cpu) = NULL;
	}

	return 0;
}
