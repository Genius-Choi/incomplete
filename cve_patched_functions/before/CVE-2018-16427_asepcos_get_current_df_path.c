static int asepcos_get_current_df_path(sc_card_t *card, sc_path_t *path)
{
	int r;
	sc_apdu_t apdu;
	u8        rbuf[SC_MAX_APDU_BUFFER_SIZE];

	sc_format_apdu(card, &apdu, SC_APDU_CASE_2_SHORT, 0xca, 0x01, 0x83); 
	apdu.resp    = rbuf;
	apdu.resplen = sizeof(rbuf);
	apdu.le      = 256;

	r = sc_transmit_apdu(card, &apdu);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
	if (apdu.sw1 != 0x90 || apdu.sw2 != 0x00)
		return sc_check_sw(card, apdu.sw1, apdu.sw2);
	return asepcos_tlvpath_to_scpath(path, apdu.resp, apdu.resplen);
}
