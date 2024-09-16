ikev1_d_print(netdissect_options *ndo, u_char tpay _U_,
	      const struct isakmp_gen *ext, u_int item_len _U_,
	      const u_char *ep _U_, uint32_t phase _U_, uint32_t doi0 _U_,
	      uint32_t proto0 _U_, int depth _U_)
{
	const struct ikev1_pl_d *p;
	struct ikev1_pl_d d;
	const uint8_t *q;
	uint32_t doi;
	uint32_t proto;
	int i;

	ND_PRINT((ndo,"%s:", NPSTR(ISAKMP_NPTYPE_D)));

	p = (const struct ikev1_pl_d *)ext;
	ND_TCHECK(*p);
	UNALIGNED_MEMCPY(&d, ext, sizeof(d));
	doi = ntohl(d.doi);
	proto = d.prot_id;
	if (doi != 1) {
		ND_PRINT((ndo," doi=%u", doi));
		ND_PRINT((ndo," proto=%u", proto));
	} else {
		ND_PRINT((ndo," doi=ipsec"));
		ND_PRINT((ndo," proto=%s", PROTOIDSTR(proto)));
	}
	ND_PRINT((ndo," spilen=%u", d.spi_size));
	ND_PRINT((ndo," nspi=%u", ntohs(d.num_spi)));
	ND_PRINT((ndo," spi="));
	q = (const uint8_t *)(p + 1);
	for (i = 0; i < ntohs(d.num_spi); i++) {
		if (i != 0)
			ND_PRINT((ndo,","));
		if (!rawprint(ndo, (const uint8_t *)q, d.spi_size))
			goto trunc;
		q += d.spi_size;
	}
	return q;
trunc:
	ND_PRINT((ndo," [|%s]", NPSTR(ISAKMP_NPTYPE_D)));
	return NULL;
}
