ikev1_p_print(netdissect_options *ndo, u_char tpay _U_,
	      const struct isakmp_gen *ext, u_int item_len _U_,
	       const u_char *ep, uint32_t phase, uint32_t doi0,
	       uint32_t proto0 _U_, int depth)
{
	const struct ikev1_pl_p *p;
	struct ikev1_pl_p prop;
	const u_char *cp;

	ND_PRINT((ndo,"%s:", NPSTR(ISAKMP_NPTYPE_P)));

	p = (const struct ikev1_pl_p *)ext;
	ND_TCHECK(*p);
	UNALIGNED_MEMCPY(&prop, ext, sizeof(prop));
	ND_PRINT((ndo," #%d protoid=%s transform=%d",
		  prop.p_no, PROTOIDSTR(prop.prot_id), prop.num_t));
	if (prop.spi_size) {
		ND_PRINT((ndo," spi="));
		if (!rawprint(ndo, (const uint8_t *)(p + 1), prop.spi_size))
			goto trunc;
	}

	ext = (const struct isakmp_gen *)((const u_char *)(p + 1) + prop.spi_size);
	ND_TCHECK(*ext);

	cp = ikev1_sub_print(ndo, ISAKMP_NPTYPE_T, ext, ep, phase, doi0,
			     prop.prot_id, depth);

	return cp;
trunc:
	ND_PRINT((ndo," [|%s]", NPSTR(ISAKMP_NPTYPE_P)));
	return NULL;
}
