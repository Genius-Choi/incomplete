auth_encode_exponent(unsigned long exponent, unsigned char *buff, size_t buff_len)
{
	int    shift;
	size_t ii;

	for (shift=0; exponent >> (shift+8); shift += 8)
		;

	for (ii = 0; ii<buff_len && shift>=0 ; ii++, shift-=8)
		*(buff + ii) = (exponent >> shift) & 0xFF;

	if (ii==buff_len)
		return 0;
	else
		return ii;
}
