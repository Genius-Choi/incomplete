authentic_pin_change_pinpad(struct sc_card *card, unsigned reference, int *tries_left)
{
	struct sc_context *ctx = card->ctx;
	struct sc_pin_cmd_data pin_cmd;
	unsigned char pin1_data[SC_MAX_APDU_BUFFER_SIZE], pin2_data[SC_MAX_APDU_BUFFER_SIZE];
	int rv;

	LOG_FUNC_CALLED(ctx);
	sc_log(ctx, "CHV PINPAD PIN reference %i", reference);

	if (!card->reader || !card->reader->ops || !card->reader->ops->perform_verify)   {
		sc_log(ctx, "Reader not ready for PIN PAD");
		LOG_FUNC_RETURN(ctx, SC_ERROR_READER);
	}

	memset(&pin_cmd, 0, sizeof(pin_cmd));
	pin_cmd.pin_type = SC_AC_CHV;
	pin_cmd.pin_reference = reference;
	pin_cmd.cmd = SC_PIN_CMD_CHANGE;
	pin_cmd.flags |= SC_PIN_CMD_USE_PINPAD | SC_PIN_CMD_NEED_PADDING;

	rv = authentic_pin_get_policy(card, &pin_cmd);
	LOG_TEST_RET(ctx, rv, "Get 'PIN policy' error");

	memset(pin1_data, pin_cmd.pin1.pad_char, sizeof(pin1_data));
	pin_cmd.pin1.data = pin1_data;

	pin_cmd.pin1.len = pin_cmd.pin1.min_length;
	pin_cmd.pin1.max_length = 8;

	memcpy(&pin_cmd.pin2, &pin_cmd.pin1, sizeof(pin_cmd.pin1));
	memset(pin2_data, pin_cmd.pin2.pad_char, sizeof(pin2_data));
	pin_cmd.pin2.data = pin2_data;

	sc_log(ctx,
	       "PIN1 lengths max/min/pad: %"SC_FORMAT_LEN_SIZE_T"u/%"SC_FORMAT_LEN_SIZE_T"u/%"SC_FORMAT_LEN_SIZE_T"u",
	       pin_cmd.pin1.max_length, pin_cmd.pin1.min_length,
	       pin_cmd.pin1.pad_length);
	sc_log(ctx,
	       "PIN2 lengths max/min/pad: %"SC_FORMAT_LEN_SIZE_T"u/%"SC_FORMAT_LEN_SIZE_T"u/%"SC_FORMAT_LEN_SIZE_T"u",
	       pin_cmd.pin2.max_length, pin_cmd.pin2.min_length,
	       pin_cmd.pin2.pad_length);

	rv = iso_ops->pin_cmd(card, &pin_cmd, tries_left);

	LOG_FUNC_RETURN(ctx, rv);
}
