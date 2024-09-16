authentic_manage_sdo(struct sc_card *card, struct sc_authentic_sdo *sdo, unsigned long cmd)
{
	struct sc_context *ctx = card->ctx;
	struct sc_apdu apdu;
	unsigned char *data = NULL;
	size_t data_len = 0, save_max_send = card->max_send_size;
	int rv;

	LOG_FUNC_CALLED(ctx);
	sc_log(ctx, "SDO(cmd:%lX,mech:%X,id:%X)", cmd, sdo->docp.mech, sdo->docp.id);

	rv = authentic_manage_sdo_encode(card, sdo, cmd, &data, &data_len);
	LOG_TEST_RET(ctx, rv, "Cannot encode SDO data");
	sc_log(ctx, "encoded SDO length %"SC_FORMAT_LEN_SIZE_T"u", data_len);

	sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0xDB, 0x3F, 0xFF);
	apdu.data = data;
	apdu.datalen = data_len;
	apdu.lc = data_len;
	apdu.flags |= SC_APDU_FLAGS_CHAINING;

	if (card->max_send_size > 255)
		card->max_send_size = 255;

	rv = sc_transmit_apdu(card, &apdu);
	card->max_send_size = save_max_send;
	LOG_TEST_RET(ctx, rv, "APDU transmit failed");

	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
	LOG_TEST_RET(ctx, rv, "authentic_sdo_create() SDO put data error");

	free(data);
	LOG_FUNC_RETURN(ctx, rv);
}
