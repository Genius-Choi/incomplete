static void usb_dev_complete(struct device *dev)
{
	/* Currently used only for rebinding interfaces */
	usb_resume_complete(dev);
}
