static int i8042_pm_resume_noirq(struct device *dev)
{
	if (!pm_resume_via_firmware())
		i8042_interrupt(0, NULL);

	return 0;
}
