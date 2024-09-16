auth_compute_signature(struct sc_card *card, const unsigned char *in, size_t ilen,
		unsigned char * out, size_t olen)
{
	struct sc_apdu apdu;
	unsigned char resp[SC_MAX_APDU_BUFFER_SIZE];
	int rv;

	if (!card || !in || !out)   {
		return SC_ERROR_INVALID_ARGUMENTS;
	}
	else if (ilen > 96)   {
		sc_log(card->ctx,
		       "Illegal input length %"SC_FORMAT_LEN_SIZE_T"u",
		       ilen);
		LOG_TEST_RET(card->ctx, SC_ERROR_INVALID_ARGUMENTS, "Illegal input length");
	}

	LOG_FUNC_CALLED(card->ctx);
	sc_log(card->ctx,
	       "inlen %"SC_FORMAT_LEN_SIZE_T"u, outlen %"SC_FORMAT_LEN_SIZE_T"u",
	       ilen, olen);

	sc_format_apdu(card, &apdu, SC_APDU_CASE_4_SHORT, 0x2A, 0x9E, 0x9A);
	apdu.datalen = ilen;
	apdu.data = in;
	apdu.lc = ilen;
	apdu.le = olen > 256 ? 256 : olen;
	apdu.resp = resp;
	apdu.resplen = olen;

	rv = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(card->ctx, rv, "APDU transmit failed");
	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
	LOG_TEST_RET(card->ctx, rv, "Compute signature failed");

	if (apdu.resplen > olen)   {
		sc_log(card->ctx,
		       "Compute signature failed: invalid response length %"SC_FORMAT_LEN_SIZE_T"u",
		       apdu.resplen);
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_CARD_CMD_FAILED);
	}

	memcpy(out, apdu.resp, apdu.resplen);

	LOG_FUNC_RETURN(card->ctx, apdu.resplen);
}
