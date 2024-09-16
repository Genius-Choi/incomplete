static void __exit pegasus_exit(void)
{
	usb_deregister(&pegasus_driver);
}
