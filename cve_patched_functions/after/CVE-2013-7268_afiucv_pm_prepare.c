static int afiucv_pm_prepare(struct device *dev)
{
#ifdef CONFIG_PM_DEBUG
	printk(KERN_WARNING "afiucv_pm_prepare\n");
#endif
	return 0;
}
