authentic_sm_get_wrapped_apdu(struct sc_card *card, struct sc_apdu *plain, struct sc_apdu **sm_apdu)
{
	struct sc_context *ctx = card->ctx;
	struct sc_apdu *apdu = NULL;
	int rv  = 0;

	LOG_FUNC_CALLED(ctx);

	if (!plain || !sm_apdu)
		LOG_FUNC_RETURN(ctx, SC_ERROR_INVALID_ARGUMENTS);
	sc_log(ctx,
	       "called; CLA:%X, INS:%X, P1:%X, P2:%X, data(%"SC_FORMAT_LEN_SIZE_T"u) %p",
	       plain->cla, plain->ins, plain->p1, plain->p2, plain->datalen,
	       plain->data);
	*sm_apdu = NULL;

	if ((plain->cla & 0x04)
			|| (plain->cla==0x00 && plain->ins==0x22)
			|| (plain->cla==0x00 && plain->ins==0x2A)
			|| (plain->cla==0x00 && plain->ins==0x84)
			|| (plain->cla==0x00 && plain->ins==0x88)
			|| (plain->cla==0x00 && plain->ins==0xA4)
			|| (plain->cla==0x00 && plain->ins==0xC0)
			|| (plain->cla==0x00 && plain->ins==0xCA)
			|| (plain->cla==0x80 && plain->ins==0x50)
	   )   {
		sc_log(ctx, "SM wrap is not applied for this APDU");
		LOG_FUNC_RETURN(ctx, SC_ERROR_SM_NOT_APPLIED);
	}

	if (card->sm_ctx.sm_mode != SM_MODE_TRANSMIT)
		LOG_FUNC_RETURN(ctx, SC_ERROR_SM_NOT_INITIALIZED);

	if (!card->sm_ctx.module.ops.get_apdus)
		LOG_FUNC_RETURN(ctx, SC_ERROR_NOT_SUPPORTED);

	apdu = calloc(1, sizeof(struct sc_apdu));
	if (!apdu)
		LOG_FUNC_RETURN(ctx, SC_ERROR_OUT_OF_MEMORY);
	memcpy((void *)apdu, (void *)plain, sizeof(struct sc_apdu));

	apdu->data = calloc (1, plain->datalen + 24);
	if (!apdu->data) {
		free(apdu);
		LOG_FUNC_RETURN(ctx, SC_ERROR_OUT_OF_MEMORY);
	}
   	if (plain->data && plain->datalen)
		memcpy((unsigned char *) apdu->data, plain->data, plain->datalen);

	apdu->resp = calloc (1, plain->resplen + 32);
	if (!apdu->resp) {
		free(apdu);
		LOG_FUNC_RETURN(ctx, SC_ERROR_OUT_OF_MEMORY);
	}

	card->sm_ctx.info.cmd = SM_CMD_APDU_TRANSMIT;
	card->sm_ctx.info.cmd_data = (void *)apdu;

	rv = card->sm_ctx.module.ops.get_apdus(ctx, &card->sm_ctx.info, NULL, 0, NULL);
	if (rv < 0) {
		free(apdu->resp);
		free(apdu);
	}
	LOG_TEST_RET(ctx, rv, "SM: GET_APDUS failed");

	*sm_apdu = apdu;
	LOG_FUNC_RETURN(ctx, SC_SUCCESS);
}
