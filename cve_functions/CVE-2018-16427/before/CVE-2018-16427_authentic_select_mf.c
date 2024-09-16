authentic_select_mf(struct sc_card *card, struct sc_file **file_out)
{
	struct sc_context *ctx = card->ctx;
	struct sc_path mfpath;
	int rv;

	struct sc_apdu apdu;
	unsigned char rbuf[SC_MAX_APDU_BUFFER_SIZE];

	LOG_FUNC_CALLED(ctx);

	sc_format_path("3F00", &mfpath);
	mfpath.type = SC_PATH_TYPE_PATH;

	if (card->cache.valid == 1
			&& card->cache.current_df
			&& card->cache.current_df->path.len == 2
			&& !memcmp(card->cache.current_df->path.value, "\x3F\x00", 2))   {
		if (file_out)
			sc_file_dup(file_out, card->cache.current_df);

		LOG_FUNC_RETURN(ctx, SC_SUCCESS);
	}

	sc_format_apdu(card, &apdu, SC_APDU_CASE_2_SHORT, 0xA4, 0x00, 0x00);

	apdu.resp = rbuf;
	apdu.resplen = sizeof(rbuf);

	rv = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(ctx, rv, "APDU transmit failed");
	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
	LOG_TEST_RET(ctx, rv, "authentic_select_file() check SW failed");

	if (card->cache.valid == 1)   {
		sc_file_free(card->cache.current_df);
		card->cache.current_df = NULL;

		sc_file_free(card->cache.current_ef);
		card->cache.current_ef = NULL;
	}

	rv = authentic_set_current_files(card, &mfpath, apdu.resp, apdu.resplen, file_out);
	LOG_TEST_RET(ctx, rv, "authentic_select_file() cannot set 'current_file'");

	LOG_FUNC_RETURN(ctx, rv);
}
