static int corsair_event(struct hid_device *dev, struct hid_field *field,
			 struct hid_usage *usage, __s32 value)
{
	struct corsair_drvdata *drvdata = hid_get_drvdata(dev);

	if (!drvdata->k90)
		return 0;

	switch (usage->hid & HID_USAGE) {
	case CORSAIR_USAGE_MACRO_RECORD_START:
		drvdata->k90->record_led.brightness = 1;
		break;
	case CORSAIR_USAGE_MACRO_RECORD_STOP:
		drvdata->k90->record_led.brightness = 0;
		break;
	default:
		break;
	}

	return 0;
}
