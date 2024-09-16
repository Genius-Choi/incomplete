static ssize_t sched_mc_power_savings_store(struct sysdev_class *class,
					    struct sysdev_class_attribute *attr,
					    const char *buf, size_t count)
{
	return sched_power_savings_store(buf, count, 0);
}
