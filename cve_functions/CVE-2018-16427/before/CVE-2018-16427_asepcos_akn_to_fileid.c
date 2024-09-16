static int asepcos_akn_to_fileid(sc_card_t *card, sc_cardctl_asepcos_akn2fileid_t *p)
{
	int r;
	u8  sbuf[32], rbuf[SC_MAX_APDU_BUFFER_SIZE];
	sc_apdu_t apdu;

	sbuf[0] = p->akn & 0xff;
	sc_format_apdu(card, &apdu, SC_APDU_CASE_4_SHORT, 0x28, 0x02, 0x01);
	apdu.cla    |= 0x80;
	apdu.resp    = rbuf;
	apdu.resplen = sizeof(rbuf);
	apdu.le      = 256;
	apdu.lc      = 1;
	apdu.datalen = 1;
	apdu.data    = sbuf;

	r = sc_transmit_apdu(card, &apdu);
	SC_TEST_RET(card->ctx, SC_LOG_DEBUG_NORMAL, r, "APDU transmit failed");

	if (apdu.resplen != 4)
		return SC_ERROR_INTERNAL;

	p->fileid = (apdu.resp[1] << 16) | (apdu.resp[2] << 8) | apdu.resp[3];

	return SC_SUCCESS;
}
