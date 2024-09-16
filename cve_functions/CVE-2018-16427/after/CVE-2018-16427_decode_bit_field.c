static int decode_bit_field(const u8 * inbuf, size_t inlen, void *outbuf, size_t outlen)
{
	u8		data[sizeof(unsigned int)];
	unsigned int	field = 0;
	int		i, n;

	if (outlen != sizeof(data))
		return SC_ERROR_BUFFER_TOO_SMALL;

	n = decode_bit_string(inbuf, inlen, data, sizeof(data), 1);
	if (n < 0)
		return n;

	for (i = 0; i < n; i += 8) {
		field |= (data[i/8] << i);
	}
	memcpy(outbuf, &field, outlen);
	return 0;
}
