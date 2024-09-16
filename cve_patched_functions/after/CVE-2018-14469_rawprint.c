rawprint(netdissect_options *ndo, const uint8_t *loc, size_t len)
{
	ND_TCHECK2(*loc, len);

	hexprint(ndo, loc, len);
	return 1;
trunc:
	return 0;
}
