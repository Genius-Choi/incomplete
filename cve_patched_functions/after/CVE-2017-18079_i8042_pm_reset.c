static int i8042_pm_reset(struct device *dev)
{
	i8042_controller_reset(false);

	return 0;
}
