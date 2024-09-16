IW_IMPL(void) iw_set_ui32be(iw_byte *b, unsigned int n)
{
	b[0] = (n>>24)&0xff;
	b[1] = (n>>16)&0xff;
	b[2] = (n>>8)&0xff;
	b[3] = n&0xff;
}
