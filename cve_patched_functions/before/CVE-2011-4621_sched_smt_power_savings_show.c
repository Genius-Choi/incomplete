static ssize_t sched_smt_power_savings_show(struct sysdev_class *dev,
					    struct sysdev_class_attribute *attr,
					    char *page)
{
	return sprintf(page, "%u\n", sched_smt_power_savings);
}
