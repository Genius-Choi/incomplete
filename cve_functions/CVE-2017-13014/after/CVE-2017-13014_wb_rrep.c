wb_rrep(netdissect_options *ndo,
        const struct pkt_rrep *rrep, u_int len)
{
	const struct pkt_dop *dop = &rrep->pr_dop;

	ND_PRINT((ndo, " wb-rrep:"));
	if (len < sizeof(*rrep) || !ND_TTEST(*rrep))
		return (-1);
	len -= sizeof(*rrep);

	ND_PRINT((ndo, " for %s %s:%u<%u:%u>",
	    ipaddr_string(ndo, &rrep->pr_id),
	    ipaddr_string(ndo, &dop->pd_page.p_sid),
	    EXTRACT_32BITS(&dop->pd_page.p_uid),
	    EXTRACT_32BITS(&dop->pd_sseq),
	    EXTRACT_32BITS(&dop->pd_eseq)));

	if (ndo->ndo_vflag)
		return (wb_dops(ndo, dop,
		    EXTRACT_32BITS(&dop->pd_sseq),
		    EXTRACT_32BITS(&dop->pd_eseq)));
	return (0);
}
