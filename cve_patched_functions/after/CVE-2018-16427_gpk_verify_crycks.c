gpk_verify_crycks(sc_card_t *card, sc_apdu_t *apdu, u8 *crycks)
{
	if (apdu->resplen < 3
	 || memcmp(apdu->resp + apdu->resplen - 3, crycks, 3)) {
		sc_debug(card->ctx, SC_LOG_DEBUG_NORMAL,
			"Invalid secure messaging reply\n");
		return SC_ERROR_UNKNOWN_DATA_RECEIVED;
	}
	apdu->resplen -= 3;
	return 0;
}
