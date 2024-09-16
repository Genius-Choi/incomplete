static void usbhid_set_leds(struct hid_device *hid)
{
	struct hid_field *field;
	int offset;

	if ((offset = hid_find_field_early(hid, HID_UP_LED, 0x01, &field)) != -1) {
		hid_set_field(field, offset, 0);
		usbhid_submit_report(hid, field->report, USB_DIR_OUT);
	}
}
