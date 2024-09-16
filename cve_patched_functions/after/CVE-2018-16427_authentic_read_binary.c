authentic_read_binary(struct sc_card *card, unsigned int idx,
		unsigned char *buf, size_t count, unsigned long flags)
{
	struct sc_context *ctx = card->ctx;
	struct sc_apdu apdu;
	size_t sz, rest, ret_count = 0;
	int rv = SC_SUCCESS;

	LOG_FUNC_CALLED(ctx);
	sc_log(ctx,
	       "offs:%i,count:%"SC_FORMAT_LEN_SIZE_T"u,max_recv_size:%"SC_FORMAT_LEN_SIZE_T"u",
	       idx, count, card->max_recv_size);

	rest = count;
	while(rest)   {
		sz = rest > 256 ? 256 : rest;
		sc_format_apdu(card, &apdu, SC_APDU_CASE_2_SHORT, 0xB0, (idx >> 8) & 0x7F, idx & 0xFF);
		apdu.le = sz;
		apdu.resplen = sz;
		apdu.resp = (buf + ret_count);

		rv = sc_transmit_apdu(card, &apdu);
		if(!rv)
			ret_count += apdu.resplen;
		else
			break;

		idx += sz;
		rest -= sz;
	}

	if (rv)   {
		LOG_TEST_RET(ctx, SC_ERROR_INTERNAL, "authentic_read_binary() failed");
		LOG_FUNC_RETURN(ctx, count);
	}

	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
	if (!rv)
		count = ret_count;

	LOG_TEST_RET(ctx, rv, "authentic_read_binary() failed");
	LOG_FUNC_RETURN(ctx, count);
}
