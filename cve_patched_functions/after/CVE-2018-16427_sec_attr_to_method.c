static unsigned int sec_attr_to_method(unsigned int attr)
{
	if (attr == 0xFF)
		return SC_AC_NEVER;
	else if (attr == 0)
		return SC_AC_NONE;
	else if (attr & 0x03)
		return SC_AC_CHV;
	else
		return SC_AC_UNKNOWN;
}
