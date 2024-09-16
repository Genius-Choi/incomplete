static int coolkey_get_challenge(sc_card_t *card, u8 *rnd, size_t len)
{
	LOG_FUNC_CALLED(card->ctx);

	if (len > COOLKEY_MAX_CHUNK_SIZE)
		len = COOLKEY_MAX_CHUNK_SIZE;

	LOG_TEST_RET(card->ctx,
			coolkey_apdu_io(card, COOLKEY_CLASS, COOLKEY_INS_GET_RANDOM, 0, 0,
				NULL, 0, &rnd, &len,  NULL, 0),
			"Could not get challenge");

	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_NORMAL, (int) len);
}
