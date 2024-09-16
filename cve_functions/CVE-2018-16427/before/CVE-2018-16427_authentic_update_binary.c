authentic_update_binary(struct sc_card *card, unsigned int idx,
		const unsigned char *buf, size_t count, unsigned long flags)
{
	struct sc_context *ctx = card->ctx;
	struct sc_apdu apdu;
	size_t sz, rest;
	int rv = SC_SUCCESS;

	LOG_FUNC_CALLED(ctx);
	sc_log(ctx,
	       "offs:%i,count:%"SC_FORMAT_LEN_SIZE_T"u,max_send_size:%"SC_FORMAT_LEN_SIZE_T"u",
	       idx, count, card->max_send_size);

	rest = count;
	while(rest)   {
		sz = rest > 255 ? 255 : rest;
		sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0xD6, (idx >> 8) & 0x7F, idx & 0xFF);
		apdu.lc = sz;
		apdu.datalen = sz;
		apdu.data = buf + count - rest;

		rv = sc_transmit_apdu(card, &apdu);
		if(rv)
			break;

		idx += sz;
		rest -= sz;
	}

	if (rv)
	{
		LOG_TEST_RET(ctx, SC_ERROR_INTERNAL, "authentic_update_binary() failed");
		LOG_FUNC_RETURN(ctx, count);
	}

	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);

	LOG_TEST_RET(ctx, rv, "authentic_update_binary() failed");
	LOG_FUNC_RETURN(ctx, count);
}
