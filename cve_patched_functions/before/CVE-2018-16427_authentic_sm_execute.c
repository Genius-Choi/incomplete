authentic_sm_execute (struct sc_card *card, struct sm_info *sm_info,
		unsigned char *data, int data_len, unsigned char *out, size_t len)
{
	struct sc_context *ctx = card->ctx;
	struct sc_remote_data rdata;
	int rv, ii;

	if (!card->sm_ctx.module.ops.get_apdus)
		LOG_FUNC_RETURN(ctx, SC_ERROR_NOT_SUPPORTED);

	sc_remote_data_init(&rdata);
	rv = card->sm_ctx.module.ops.get_apdus(ctx, sm_info, data, data_len, &rdata);
	LOG_TEST_RET(ctx, rv, "SM: GET_APDUS failed");
	if (!rdata.length)
		LOG_FUNC_RETURN(ctx, SC_ERROR_INTERNAL);

	sc_log(ctx, "GET_APDUS: rv %i; rdata length %i", rv, rdata.length);

	for (ii=0; ii < rdata.length; ii++)   {
		struct sc_apdu *apdu = &((rdata.data + ii)->apdu);

		if (!apdu->ins)
			break;
		rv = sc_transmit_apdu(card, apdu);
		if (rv < 0)
			break;

		rv = sc_check_sw(card, apdu->sw1, apdu->sw2);
		if (rv < 0)
			break;
	}

	rdata.free(&rdata);
	LOG_FUNC_RETURN(ctx, rv);
}
