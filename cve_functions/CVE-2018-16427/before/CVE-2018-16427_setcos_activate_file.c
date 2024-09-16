static int setcos_activate_file(sc_card_t *card)
{
	int r;
	u8 sbuf[2];
	sc_apdu_t apdu;

	sc_format_apdu(card, &apdu, SC_APDU_CASE_1, 0x44, 0x00, 0x00);
	apdu.data = sbuf;

	r = sc_transmit_apdu(card, &apdu);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");

	r = sc_check_sw(card, apdu.sw1, apdu.sw2);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "ACTIVATE_FILE returned error");

	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_NORMAL, r);
}
