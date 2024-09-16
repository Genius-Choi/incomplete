auth_read_record(struct sc_card *card, unsigned int nr_rec,
		unsigned char *buf, size_t count, unsigned long flags)
{
	struct sc_apdu apdu;
	int rv = 0;
	unsigned char recvbuf[SC_MAX_APDU_BUFFER_SIZE];

	sc_log(card->ctx,
	       "auth_read_record(): nr_rec %i; count %"SC_FORMAT_LEN_SIZE_T"u",
	       nr_rec, count);

	sc_format_apdu(card, &apdu, SC_APDU_CASE_2_SHORT, 0xB2, nr_rec, 0);
	apdu.p2 = (flags & SC_RECORD_EF_ID_MASK) << 3;
	if (flags & SC_RECORD_BY_REC_NR)
		apdu.p2 |= 0x04;

	apdu.le = count;
	apdu.resplen = count;
	apdu.resp = recvbuf;

	rv = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(card->ctx, rv, "APDU transmit failed");
	if (apdu.resplen == 0)
		LOG_FUNC_RETURN(card->ctx, sc_check_sw(card, apdu.sw1, apdu.sw2));
	memcpy(buf, recvbuf, apdu.resplen);

	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
	LOG_TEST_RET(card->ctx, rv, "Card returned error");

	LOG_FUNC_RETURN(card->ctx, apdu.resplen);
}
