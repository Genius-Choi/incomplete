ikev2_nonce_print(netdissect_options *ndo, u_char tpay,
		const struct isakmp_gen *ext,
		u_int item_len _U_, const u_char *ep,
		uint32_t phase _U_, uint32_t doi _U_,
		uint32_t proto _U_, int depth _U_)
{
	struct isakmp_gen e;

	ND_TCHECK(*ext);
	UNALIGNED_MEMCPY(&e, ext, sizeof(e));
	ikev2_pay_print(ndo, "nonce", e.critical);

	ND_PRINT((ndo," len=%d", ntohs(e.len) - 4));
	if (1 < ndo->ndo_vflag && 4 < ntohs(e.len)) {
		ND_PRINT((ndo," nonce=("));
		if (!rawprint(ndo, (const uint8_t *)(ext + 1), ntohs(e.len) - 4))
			goto trunc;
		ND_PRINT((ndo,") "));
	} else if(ndo->ndo_vflag && 4 < ntohs(e.len)) {
		if(!ike_show_somedata(ndo, (const u_char *)(ext+1), ep)) goto trunc;
	}

	return (const u_char *)ext + ntohs(e.len);
trunc:
	ND_PRINT((ndo," [|%s]", NPSTR(tpay)));
	return NULL;
}
