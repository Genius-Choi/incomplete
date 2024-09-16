static void corsair_remove(struct hid_device *dev)
{
	k90_cleanup_macro_functions(dev);
	k90_cleanup_backlight(dev);

	hid_hw_stop(dev);
}
