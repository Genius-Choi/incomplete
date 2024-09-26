gre_sre_print(netdissect_options *ndo, uint16_t af, uint8_t sreoff,
    uint8_t srelen, const u_char *bp, u_int len)
{
	int ret;

	switch (af) {
	case GRESRE_IP:
		ND_PRINT((ndo, ", (rtaf=ip"));
		ret = gre_sre_ip_print(ndo, sreoff, srelen, bp, len);
		ND_PRINT((ndo, ")"));
		break;
	case GRESRE_ASN:
		ND_PRINT((ndo, ", (rtaf=asn"));
		ret = gre_sre_asn_print(ndo, sreoff, srelen, bp, len);
		ND_PRINT((ndo, ")"));
		break;
	default:
		ND_PRINT((ndo, ", (rtaf=0x%x)", af));
		ret = 1;
	}
	return (ret);
}
