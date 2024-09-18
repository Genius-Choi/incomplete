static int asepcos_change_key(sc_card_t *card, sc_cardctl_asepcos_change_key_t *p)
{
	int       r, atype;
	sc_apdu_t apdu;

	if (p->datalen > 255)
		atype = SC_APDU_CASE_3_EXT;
	else
		atype = SC_APDU_CASE_3_SHORT;

	sc_format_apdu(card, &apdu, atype, 0x24, 0x01, 0x80);
	apdu.lc      = p->datalen;
	apdu.datalen = p->datalen;
	apdu.data    = p->data;

	r = sc_transmit_apdu(card, &apdu);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
	return sc_check_sw(card, apdu.sw1, apdu.sw2);
}
