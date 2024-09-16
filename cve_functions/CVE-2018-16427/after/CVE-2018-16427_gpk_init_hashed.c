gpk_init_hashed(sc_card_t *card, const u8 *digest, unsigned int len)
{
	sc_apdu_t	apdu;
	u8		tsegid[64];
	int		r;

	r = reverse(tsegid, sizeof(tsegid), digest, len);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "Failed to reverse buffer");

	memset(&apdu, 0, sizeof(apdu));
	apdu.cse = SC_APDU_CASE_3_SHORT;
	apdu.cla = 0x80;
	apdu.ins = 0xEA;
	apdu.lc  = len;
	apdu.data= tsegid;
	apdu.datalen = len;

	r = sc_transmit_apdu(card, &apdu);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
	r = sc_check_sw(card, apdu.sw1, apdu.sw2);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "Card returned error");

	return r;
}
