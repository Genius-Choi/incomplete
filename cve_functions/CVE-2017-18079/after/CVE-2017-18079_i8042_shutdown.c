static void i8042_shutdown(struct platform_device *dev)
{
	i8042_controller_reset(false);
}
