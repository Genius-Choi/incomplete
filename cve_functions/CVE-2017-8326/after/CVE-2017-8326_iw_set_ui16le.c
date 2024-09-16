IW_IMPL(void) iw_set_ui16le(iw_byte *b, unsigned int n)
{
	b[0] = n&0xff;
	b[1] = (n>>8)&0xff;
}
