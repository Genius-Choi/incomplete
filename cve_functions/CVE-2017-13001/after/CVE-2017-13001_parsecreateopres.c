parsecreateopres(netdissect_options *ndo,
                 const uint32_t *dp, int verbose)
{
	int er;

	if (!(dp = parsestatus(ndo, dp, &er)))
		return (0);
	if (er)
		dp = parse_wcc_data(ndo, dp, verbose);
	else {
		ND_TCHECK(dp[0]);
		if (!EXTRACT_32BITS(&dp[0]))
			return (dp + 1);
		dp++;
		if (!(dp = parsefh(ndo, dp, 1)))
			return (0);
		if (verbose) {
			if (!(dp = parse_post_op_attr(ndo, dp, verbose)))
				return (0);
			if (ndo->ndo_vflag > 1) {
				ND_PRINT((ndo, " dir attr:"));
				dp = parse_wcc_data(ndo, dp, verbose);
			}
		}
	}
	return (dp);
trunc:
	return (NULL);
}
