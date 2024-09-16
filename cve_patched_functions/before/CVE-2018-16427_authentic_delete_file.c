authentic_delete_file(struct sc_card *card, const struct sc_path *path)
{
	struct sc_context *ctx = card->ctx;
	struct sc_apdu apdu;
	unsigned char p1;
	int rv, ii;

	LOG_FUNC_CALLED(ctx);

	if (!path)
		LOG_FUNC_RETURN(ctx, SC_ERROR_INVALID_ARGUMENTS);

	for (ii=0, p1 = 0x02; ii<2; ii++, p1 = 0x01)   {
		sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0xE4, p1, 0x00);
		apdu.data = path->value + path->len - 2;
		apdu.datalen = 2;
		apdu.lc = 2;

		rv = sc_transmit_apdu(card, &apdu);
		LOG_TEST_RET(ctx, rv, "APDU transmit failed");
		rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
		if (rv != SC_ERROR_FILE_NOT_FOUND || p1 != 0x02)
			break;
	}
	LOG_TEST_RET(ctx, rv, "Delete file failed");

	if (card->cache.valid)   {
		sc_file_free(card->cache.current_ef);
		card->cache.current_ef = NULL;
	}

	LOG_FUNC_RETURN(ctx, rv);
}
