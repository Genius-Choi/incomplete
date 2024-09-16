static bool i8042_filter(unsigned char data, unsigned char str,
			 struct serio *serio)
{
	if (unlikely(i8042_suppress_kbd_ack)) {
		if ((~str & I8042_STR_AUXDATA) &&
		    (data == 0xfa || data == 0xfe)) {
			i8042_suppress_kbd_ack--;
			dbg("Extra keyboard ACK - filtered out\n");
			return true;
		}
	}

	if (i8042_platform_filter && i8042_platform_filter(data, str, serio)) {
		dbg("Filtered out by platform filter\n");
		return true;
	}

	return false;
}
