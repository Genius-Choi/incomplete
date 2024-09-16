set_taglength_tlv(u8 *buffer, unsigned int tag, size_t length)
{
	u8 *p = buffer;

	assert(tag <= 0xffff);
	if (tag > 0xff)
		*p++ = (tag >> 8) & 0xFF;
	*p++ = tag;
	if (length < 128)
		*p++ = (u8)length;
	else if (length < 256) {
		*p++ = 0x81;
		*p++ = (u8)length;
	}
	else {
		if (length > 0xffff)
			length = 0xffff;
		*p++ = 0x82;
		*p++ = (length >> 8) & 0xFF;
		*p++ = length & 0xFF;
	}

	return p - buffer;
}
