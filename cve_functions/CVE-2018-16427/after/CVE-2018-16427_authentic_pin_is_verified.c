authentic_pin_is_verified(struct sc_card *card, struct sc_pin_cmd_data *pin_cmd_data,
		int *tries_left)
{
	struct sc_context *ctx = card->ctx;
	struct sc_pin_cmd_data pin_cmd;
	int rv;

	LOG_FUNC_CALLED(ctx);

	if (pin_cmd_data->pin_type != SC_AC_CHV)
		LOG_TEST_RET(ctx, SC_ERROR_NOT_SUPPORTED, "PIN type is not supported for the verification");

	pin_cmd = *pin_cmd_data;
	pin_cmd.pin1.data = (unsigned char *)"";
	pin_cmd.pin1.len = 0;

	rv = authentic_chv_verify(card, &pin_cmd, tries_left);

	LOG_FUNC_RETURN(ctx, rv);
}
