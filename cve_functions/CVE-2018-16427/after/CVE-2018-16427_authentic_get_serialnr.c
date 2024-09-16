authentic_get_serialnr(struct sc_card *card, struct sc_serial_number *serial)
{
	struct sc_context *ctx = card->ctx;
	struct authentic_private_data *prv_data = (struct authentic_private_data *) card->drv_data;
	int rv;

	LOG_FUNC_CALLED(ctx);
	if (!card->serialnr.len)   {
		rv = authentic_get_cplc(card);
		LOG_TEST_RET(ctx, rv, "get CPLC data error");

		card->serialnr.len = 4;
		memcpy(card->serialnr.value, prv_data->cplc.value + 15, 4);

		sc_log(ctx, "serial %02X%02X%02X%02X",
				card->serialnr.value[0], card->serialnr.value[1],
				card->serialnr.value[2], card->serialnr.value[3]);
	}

	if (serial)
		memcpy(serial, &card->serialnr, sizeof(*serial));

	LOG_FUNC_RETURN(ctx, SC_SUCCESS);
}
