auth_read_component(struct sc_card *card, enum SC_CARDCTL_OBERTHUR_KEY_TYPE type,
		int num, unsigned char *out, size_t outlen)
{
	struct sc_apdu apdu;
	int rv;
	unsigned char resp[256];

	LOG_FUNC_CALLED(card->ctx);
	sc_log(card->ctx, "num %i, outlen %"SC_FORMAT_LEN_SIZE_T"u, type %i",
	       num, outlen, type);

	if (!outlen || type!=SC_CARDCTL_OBERTHUR_KEY_RSA_PUBLIC)
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_INCORRECT_PARAMETERS);

	sc_format_apdu(card, &apdu, SC_APDU_CASE_2_SHORT, 0xB4,	num, 0x00);
	apdu.cla |= 0x80;
	apdu.le = outlen;
	apdu.resp = resp;
	apdu.resplen = sizeof(resp);
	rv = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(card->ctx, rv, "APDU transmit failed");

	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
	LOG_TEST_RET(card->ctx, rv, "Card returned error");

	if (outlen < apdu.resplen)
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_WRONG_LENGTH);

	memcpy(out, apdu.resp, apdu.resplen);
	LOG_FUNC_RETURN(card->ctx, apdu.resplen);
}
