print_16bits_val(netdissect_options *ndo, const uint16_t *dat)
{
	ND_PRINT((ndo, "%u", EXTRACT_16BITS(dat)));
}
