dhcp6stcode(const uint16_t code)
{
	return code > 255 ? "INVALID code" : tok2str(dh6opt_stcode_str, "code%u", code);
}
