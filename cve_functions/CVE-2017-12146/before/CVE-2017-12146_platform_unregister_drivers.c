void platform_unregister_drivers(struct platform_driver * const *drivers,
				 unsigned int count)
{
	while (count--) {
		pr_debug("unregistering platform driver %ps\n", drivers[count]);
		platform_driver_unregister(drivers[count]);
	}
}
