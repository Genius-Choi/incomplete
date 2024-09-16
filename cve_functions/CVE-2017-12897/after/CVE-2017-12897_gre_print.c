gre_print(netdissect_options *ndo, const u_char *bp, u_int length)
{
	u_int len = length, vers;

	ND_TCHECK2(*bp, 2);
	if (len < 2)
		goto trunc;
	vers = EXTRACT_16BITS(bp) & GRE_VERS_MASK;
        ND_PRINT((ndo, "GREv%u",vers));

        switch(vers) {
        case 0:
            gre_print_0(ndo, bp, len);
            break;
        case 1:
            gre_print_1(ndo, bp, len);
            break;
	default:
            ND_PRINT((ndo, " ERROR: unknown-version"));
            break;
        }
        return;

trunc:
	ND_PRINT((ndo, "%s", tstr));
	return;
}
