print_octets(netdissect_options *ndo, const u_char *dat, u_int length)
{
	u_int i;
	for (i=0; i<length; i++) {
		ND_PRINT((ndo, "%02x", *dat++));
	}
}
