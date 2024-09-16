static void pmu_dev_release(struct device *dev)
{
	kfree(dev);
}
