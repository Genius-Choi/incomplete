auth_get_serialnr(struct sc_card *card, struct sc_serial_number *serial)
{
	if (!serial)
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_INVALID_ARGUMENTS);

	if (card->serialnr.len==0)
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_INTERNAL);

	memcpy(serial, &card->serialnr, sizeof(*serial));

	LOG_FUNC_RETURN(card->ctx, SC_SUCCESS);
}
