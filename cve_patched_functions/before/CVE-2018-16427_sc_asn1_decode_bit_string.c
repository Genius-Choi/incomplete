int sc_asn1_decode_bit_string(const u8 * inbuf, size_t inlen,
			      void *outbuf, size_t outlen)
{
	return decode_bit_string(inbuf, inlen, outbuf, outlen, 1);
}
