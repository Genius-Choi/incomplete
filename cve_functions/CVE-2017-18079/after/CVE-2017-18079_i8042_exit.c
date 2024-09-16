static void __exit i8042_exit(void)
{
	platform_device_unregister(i8042_platform_device);
	platform_driver_unregister(&i8042_driver);
	i8042_platform_exit();

	bus_unregister_notifier(&serio_bus, &i8042_kbd_bind_notifier_block);
	panic_blink = NULL;
}
