IW_IMPL(void) iw_set_ui16be(iw_byte *b, unsigned int n)
{
	b[0] = (n>>8)&0xff;
	b[1] = n&0xff;
}
