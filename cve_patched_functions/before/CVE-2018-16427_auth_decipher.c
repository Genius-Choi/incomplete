auth_decipher(struct sc_card *card, const unsigned char *in, size_t inlen,
				unsigned char *out, size_t outlen)
{
	struct sc_apdu apdu;
	unsigned char resp[SC_MAX_APDU_BUFFER_SIZE];
	int rv, _inlen = inlen;

	LOG_FUNC_CALLED(card->ctx);
	sc_log(card->ctx,
	       "crgram_len %"SC_FORMAT_LEN_SIZE_T"u;  outlen %"SC_FORMAT_LEN_SIZE_T"u",
	       inlen, outlen);
	if (!out || !outlen || inlen > SC_MAX_APDU_BUFFER_SIZE)
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_INVALID_ARGUMENTS);

	sc_format_apdu(card, &apdu, SC_APDU_CASE_4_SHORT, 0x2A, 0x80, 0x86);

	sc_log(card->ctx, "algorithm SC_ALGORITHM_RSA");
	if (inlen % 64)   {
		rv = SC_ERROR_INVALID_ARGUMENTS;
		goto done;
	}

	_inlen = inlen;
	if (_inlen == 256)   {
		apdu.cla |= 0x10;
		apdu.data = in;
		apdu.datalen = 8;
		apdu.resp = resp;
		apdu.resplen = SC_MAX_APDU_BUFFER_SIZE;
		apdu.lc = 8;
		apdu.le = 256;

		rv = sc_transmit_apdu(card, &apdu);
		sc_log(card->ctx, "rv %i", rv);
		LOG_TEST_RET(card->ctx, rv, "APDU transmit failed");
		rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
		LOG_TEST_RET(card->ctx, rv, "Card returned error");

		_inlen -= 8;
		in += 8;

		apdu.cla &= ~0x10;
	}

	apdu.data = in;
	apdu.datalen = _inlen;
	apdu.resp = resp;
	apdu.resplen = SC_MAX_APDU_BUFFER_SIZE;
	apdu.lc = _inlen;
	apdu.le = _inlen;

	rv = sc_transmit_apdu(card, &apdu);
	sc_log(card->ctx, "rv %i", rv);
	LOG_TEST_RET(card->ctx, rv, "APDU transmit failed");
	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
	sc_log(card->ctx, "rv %i", rv);
	LOG_TEST_RET(card->ctx, rv, "Card returned error");

	if (outlen > apdu.resplen)
		outlen = apdu.resplen;

	memcpy(out, apdu.resp, outlen);
	rv = outlen;

done:
	LOG_FUNC_RETURN(card->ctx, rv);
}
