static int lg_input_mapping(struct hid_device *hdev, struct hid_input *hi,
		struct hid_field *field, struct hid_usage *usage,
		unsigned long **bit, int *max)
{
	/* extended mapping for certain Logitech hardware (Logitech cordless
	   desktop LX500) */
	static const u8 e_keymap[] = {
		  0,216,  0,213,175,156,  0,  0,  0,  0,
		144,  0,  0,  0,  0,  0,  0,  0,  0,212,
		174,167,152,161,112,  0,  0,  0,154,  0,
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
		  0,  0,  0,  0,  0,183,184,185,186,187,
		188,189,190,191,192,193,194,  0,  0,  0
	};
	struct lg_drv_data *drv_data = hid_get_drvdata(hdev);
	unsigned int hid = usage->hid;

	if (hdev->product == USB_DEVICE_ID_LOGITECH_RECEIVER &&
			lg_ultrax_remote_mapping(hi, usage, bit, max))
		return 1;

	if (hdev->product == USB_DEVICE_ID_DINOVO_MINI &&
			lg_dinovo_mapping(hi, usage, bit, max))
		return 1;

	if ((drv_data->quirks & LG_WIRELESS) && lg_wireless_mapping(hi, usage, bit, max))
		return 1;

	if ((hid & HID_USAGE_PAGE) != HID_UP_BUTTON)
		return 0;

	hid &= HID_USAGE;

	/* Special handling for Logitech Cordless Desktop */
	if (field->application == HID_GD_MOUSE) {
		if ((drv_data->quirks & LG_IGNORE_DOUBLED_WHEEL) &&
				(hid == 7 || hid == 8))
			return -1;
	} else {
		if ((drv_data->quirks & LG_EXPANDED_KEYMAP) &&
				hid < ARRAY_SIZE(e_keymap) &&
				e_keymap[hid] != 0) {
			hid_map_usage(hi, usage, bit, max, EV_KEY,
					e_keymap[hid]);
			return 1;
		}
	}

	return 0;
}
