static int magicmouse_input_mapping(struct hid_device *hdev,
		struct hid_input *hi, struct hid_field *field,
		struct hid_usage *usage, unsigned long **bit, int *max)
{
	struct magicmouse_sc *msc = hid_get_drvdata(hdev);

	if (!msc->input)
		msc->input = hi->input;

	/* Magic Trackpad does not give relative data after switching to MT */
	if (hi->input->id.product == USB_DEVICE_ID_APPLE_MAGICTRACKPAD &&
	    field->flags & HID_MAIN_ITEM_RELATIVE)
		return -1;

	return 0;
}
