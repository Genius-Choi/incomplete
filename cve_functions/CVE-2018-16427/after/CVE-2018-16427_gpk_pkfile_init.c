gpk_pkfile_init(sc_card_t *card, struct sc_cardctl_gpk_pkinit *args)
{
	sc_apdu_t	apdu;
	int		r;

	sc_debug(card->ctx, SC_LOG_DEBUG_NORMAL,
		"gpk_pkfile_init(%u)\n", args->privlen);

	memset(&apdu, 0, sizeof(apdu));
	apdu.cse = SC_APDU_CASE_1;
	apdu.cla = 0x80;
	apdu.ins = 0x12;
	apdu.p1  = args->file->id & 0x1F;
	apdu.p2  = args->privlen / 4;

	r = sc_transmit_apdu(card, &apdu);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
	r = sc_check_sw(card, apdu.sw1, apdu.sw2);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "Card returned error");

	return r;
}
