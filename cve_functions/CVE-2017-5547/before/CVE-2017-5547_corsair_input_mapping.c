static int corsair_input_mapping(struct hid_device *dev,
				 struct hid_input *input,
				 struct hid_field *field,
				 struct hid_usage *usage, unsigned long **bit,
				 int *max)
{
	int gkey;

	if ((usage->hid & HID_USAGE_PAGE) != HID_UP_KEYBOARD)
		return 0;

	gkey = corsair_usage_to_gkey(usage->hid & HID_USAGE);
	if (gkey != 0) {
		hid_map_usage_clear(input, usage, bit, max, EV_KEY,
				    corsair_gkey_map[gkey - 1]);
		return 1;
	}
	if ((usage->hid & HID_USAGE) >= CORSAIR_USAGE_SPECIAL_MIN &&
	    (usage->hid & HID_USAGE) <= CORSAIR_USAGE_SPECIAL_MAX) {
		switch (usage->hid & HID_USAGE) {
		case CORSAIR_USAGE_MACRO_RECORD_START:
			hid_map_usage_clear(input, usage, bit, max, EV_KEY,
					    corsair_record_keycodes[0]);
			return 1;

		case CORSAIR_USAGE_MACRO_RECORD_STOP:
			hid_map_usage_clear(input, usage, bit, max, EV_KEY,
					    corsair_record_keycodes[1]);
			return 1;

		case CORSAIR_USAGE_M1:
			hid_map_usage_clear(input, usage, bit, max, EV_KEY,
					    corsair_profile_keycodes[0]);
			return 1;

		case CORSAIR_USAGE_M2:
			hid_map_usage_clear(input, usage, bit, max, EV_KEY,
					    corsair_profile_keycodes[1]);
			return 1;

		case CORSAIR_USAGE_M3:
			hid_map_usage_clear(input, usage, bit, max, EV_KEY,
					    corsair_profile_keycodes[2]);
			return 1;

		default:
			return -1;
		}
	}

	return 0;
}
