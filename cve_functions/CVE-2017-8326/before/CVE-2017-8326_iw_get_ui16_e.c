IW_IMPL(unsigned int) iw_get_ui16_e(const iw_byte *b, int endian)
{
	if(endian==IW_ENDIAN_LITTLE)
		return iw_get_ui16le(b);
	return iw_get_ui16be(b);
}
