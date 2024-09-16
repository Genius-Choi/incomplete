static int i8042_remove(struct platform_device *dev)
{
	i8042_unregister_ports();
	i8042_free_irqs();
	i8042_controller_reset(false);
	i8042_platform_device = NULL;

	return 0;
}
