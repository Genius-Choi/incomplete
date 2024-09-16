authentic_chv_verify_pinpad(struct sc_card *card, struct sc_pin_cmd_data *pin_cmd, int *tries_left)
{
	struct sc_context *ctx = card->ctx;
	unsigned char buffer[0x100];
	struct sc_pin_cmd_pin *pin1 = &pin_cmd->pin1;
	int rv;

	LOG_FUNC_CALLED(ctx);
	sc_log(ctx, "Verify PIN(ref:%i) with pin-pad", pin_cmd->pin_reference);

	rv = authentic_pin_is_verified(card, pin_cmd, tries_left);
	if (!rv)
		LOG_FUNC_RETURN(ctx, rv);

	if (!card->reader || !card->reader->ops || !card->reader->ops->perform_verify)   {
		sc_log(ctx, "Reader not ready for PIN PAD");
		LOG_FUNC_RETURN(ctx, SC_ERROR_READER);
	}

	pin1->len = pin1->min_length;
	pin1->max_length = 8;

	memset(buffer, pin1->pad_char, sizeof(buffer));
	pin1->data = buffer;

	pin_cmd->cmd = SC_PIN_CMD_VERIFY;
	pin_cmd->flags |= SC_PIN_CMD_USE_PINPAD;

	rv = iso_ops->pin_cmd(card, pin_cmd, tries_left);

	LOG_FUNC_RETURN(ctx, rv);
}
