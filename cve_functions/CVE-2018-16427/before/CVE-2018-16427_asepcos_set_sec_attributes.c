static int asepcos_set_sec_attributes(sc_card_t *card, const u8 *data, size_t len,
	int is_ef)
{
	int r, type = is_ef != 0 ? 0x02 : 0x04;
	sc_apdu_t apdu;

	sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0x8a, type, 0xab);
	apdu.cla    |= 0x80;
	apdu.lc      = len;
	apdu.datalen = len;
	apdu.data    = data;
	r = sc_transmit_apdu(card, &apdu);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
	return sc_check_sw(card, apdu.sw1, apdu.sw2);
}
