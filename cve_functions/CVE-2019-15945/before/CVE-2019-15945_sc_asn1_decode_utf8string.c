static int sc_asn1_decode_utf8string(const u8 *inbuf, size_t inlen,
			      u8 *out, size_t *outlen)
{
	if (inlen+1 > *outlen)
		return SC_ERROR_BUFFER_TOO_SMALL;
	*outlen = inlen+1;
	memcpy(out, inbuf, inlen);
	out[inlen] = 0;
	return 0;
}
