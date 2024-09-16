static int rtecp_logout(sc_card_t *card)
{
	sc_apdu_t apdu;
	int r;

	assert(card && card->ctx);
	sc_format_apdu(card, &apdu, SC_APDU_CASE_1, 0x40, 0, 0);
	apdu.cla = 0x80;
	r = sc_transmit_apdu(card, &apdu);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
	r = sc_check_sw(card, apdu.sw1, apdu.sw2);
	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, r);
}
