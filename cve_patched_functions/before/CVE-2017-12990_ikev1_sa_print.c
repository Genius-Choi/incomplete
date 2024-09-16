ikev1_sa_print(netdissect_options *ndo, u_char tpay _U_,
	       const struct isakmp_gen *ext,
		u_int item_len _U_,
		const u_char *ep, uint32_t phase, uint32_t doi0 _U_,
		uint32_t proto0, int depth)
{
	const struct ikev1_pl_sa *p;
	struct ikev1_pl_sa sa;
	uint32_t doi, sit, ident;
	const u_char *cp, *np;
	int t;

	ND_PRINT((ndo,"%s:", NPSTR(ISAKMP_NPTYPE_SA)));

	p = (const struct ikev1_pl_sa *)ext;
	ND_TCHECK(*p);
	UNALIGNED_MEMCPY(&sa, ext, sizeof(sa));
	doi = ntohl(sa.doi);
	sit = ntohl(sa.sit);
	if (doi != 1) {
		ND_PRINT((ndo," doi=%d", doi));
		ND_PRINT((ndo," situation=%u", (uint32_t)ntohl(sa.sit)));
		return (const u_char *)(p + 1);
	}

	ND_PRINT((ndo," doi=ipsec"));
	ND_PRINT((ndo," situation="));
	t = 0;
	if (sit & 0x01) {
		ND_PRINT((ndo,"identity"));
		t++;
	}
	if (sit & 0x02) {
		ND_PRINT((ndo,"%ssecrecy", t ? "+" : ""));
		t++;
	}
	if (sit & 0x04)
		ND_PRINT((ndo,"%sintegrity", t ? "+" : ""));

	np = (const u_char *)ext + sizeof(sa);
	if (sit != 0x01) {
		ND_TCHECK2(*(ext + 1), sizeof(ident));
		UNALIGNED_MEMCPY(&ident, ext + 1, sizeof(ident));
		ND_PRINT((ndo," ident=%u", (uint32_t)ntohl(ident)));
		np += sizeof(ident);
	}

	ext = (const struct isakmp_gen *)np;
	ND_TCHECK(*ext);

	cp = ikev1_sub_print(ndo, ISAKMP_NPTYPE_P, ext, ep, phase, doi, proto0,
		depth);

	return cp;
trunc:
	ND_PRINT((ndo," [|%s]", NPSTR(ISAKMP_NPTYPE_SA)));
	return NULL;
}
