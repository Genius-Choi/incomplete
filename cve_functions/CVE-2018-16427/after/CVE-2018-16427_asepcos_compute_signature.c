static int asepcos_compute_signature(sc_card_t *card, const u8 *data, size_t datalen,
			 u8 *out, size_t outlen)
{
	int r = SC_SUCCESS, atype;
	u8  rbuf[SC_MAX_APDU_BUFFER_SIZE];
	sc_apdu_t apdu;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_NORMAL);

	if (datalen >= 256)
		atype = SC_APDU_CASE_4_EXT;
	else
		atype = SC_APDU_CASE_4_SHORT;
	sc_format_apdu(card, &apdu, atype, 0x14, 0x01, 0x00);
	apdu.cla    |= 0x80;
	apdu.lc      = datalen;
	apdu.datalen = datalen;
	apdu.data    = data;
	apdu.resp    = rbuf;
	apdu.resplen = sizeof(rbuf);
	apdu.le      = 256;

	r = sc_transmit_apdu(card, &apdu);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");
	if (apdu.sw1 != 0x90 || apdu.sw2 != 0x00) {
		sc_debug(card->ctx, SC_LOG_DEBUG_NORMAL, "error creating signature");
		return sc_check_sw(card, apdu.sw1, apdu.sw2);
	}

	if (apdu.resplen > outlen)
		return SC_ERROR_BUFFER_TOO_SMALL;
	memcpy(out, apdu.resp, apdu.resplen);

	return apdu.resplen;
}
