static int aiptek_open(struct input_dev *inputdev)
{
	struct aiptek *aiptek = input_get_drvdata(inputdev);

	aiptek->urb->dev = aiptek->usbdev;
	if (usb_submit_urb(aiptek->urb, GFP_KERNEL) != 0)
		return -EIO;

	return 0;
}
