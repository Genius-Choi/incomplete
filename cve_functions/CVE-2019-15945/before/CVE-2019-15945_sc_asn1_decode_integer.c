int sc_asn1_decode_integer(const u8 * inbuf, size_t inlen, int *out)
{
	int    a = 0;
	size_t i;

	if (inlen > sizeof(int) || inlen == 0)
		return SC_ERROR_INVALID_ASN1_OBJECT;
	if (inbuf[0] & 0x80)
		a = -1;
	for (i = 0; i < inlen; i++) {
		a <<= 8;
		a |= *inbuf++;
	}
	*out = a;
	return 0;
}
