IW_IMPL(int) iw_get_host_endianness(void)
{
	iw_byte b;
	unsigned int x = 1;
	memcpy(&b,&x,1);
	return b==0 ? IW_ENDIAN_BIG : IW_ENDIAN_LITTLE;
}
