hexprint(netdissect_options *ndo, const uint8_t *loc, size_t len)
{
	const uint8_t *p;
	size_t i;

	p = loc;
	for (i = 0; i < len; i++)
		ND_PRINT((ndo,"%02x", p[i] & 0xff));
}
