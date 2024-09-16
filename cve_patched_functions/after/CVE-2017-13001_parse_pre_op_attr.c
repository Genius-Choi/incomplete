parse_pre_op_attr(netdissect_options *ndo,
                  const uint32_t *dp, int verbose)
{
	ND_TCHECK(dp[0]);
	if (!EXTRACT_32BITS(&dp[0]))
		return (dp + 1);
	dp++;
	ND_TCHECK2(*dp, 24);
	if (verbose > 1) {
		return parse_wcc_attr(ndo, dp);
	} else {
		/* If not verbose enough, just skip over wcc_attr */
		return (dp + 6);
	}
trunc:
	return (NULL);
}
