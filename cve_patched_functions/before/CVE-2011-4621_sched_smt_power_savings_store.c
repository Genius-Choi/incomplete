static ssize_t sched_smt_power_savings_store(struct sysdev_class *dev,
					     struct sysdev_class_attribute *attr,
					     const char *buf, size_t count)
{
	return sched_power_savings_store(buf, count, 1);
}
