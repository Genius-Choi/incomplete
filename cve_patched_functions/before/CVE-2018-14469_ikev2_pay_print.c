ikev2_pay_print(netdissect_options *ndo, const char *payname, int critical)
{
	ND_PRINT((ndo,"%s%s:", payname, critical&0x80 ? "[C]" : ""));
}
