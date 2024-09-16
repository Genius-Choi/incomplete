static int __init pegasus_init(void)
{
	pr_info("%s: %s, " DRIVER_DESC "\n", driver_name, DRIVER_VERSION);
	if (devid)
		parse_id(devid);
	return usb_register(&pegasus_driver);
}
