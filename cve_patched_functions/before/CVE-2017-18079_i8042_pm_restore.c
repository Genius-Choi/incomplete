static int i8042_pm_restore(struct device *dev)
{
	return i8042_controller_resume(false);
}
