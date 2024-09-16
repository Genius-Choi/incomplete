auth_pin_change_pinpad(struct sc_card *card, struct sc_pin_cmd_data *data,
		int *tries_left)
{
	struct sc_card_driver *iso_drv = sc_get_iso7816_driver();
	struct sc_pin_cmd_data pin_cmd;
	struct sc_apdu apdu;
	unsigned char ffs1[0x100];
	unsigned char ffs2[0x100];
	int rv, pin_reference;

	LOG_FUNC_CALLED(card->ctx);

	pin_reference = data->pin_reference & ~OBERTHUR_PIN_LOCAL;

	memset(ffs1, 0xFF, sizeof(ffs1));
	memset(ffs2, 0xFF, sizeof(ffs2));
	memset(&pin_cmd, 0, sizeof(pin_cmd));

	if (data->pin1.len > OBERTHUR_AUTH_MAX_LENGTH_PIN)
		LOG_TEST_RET(card->ctx, SC_ERROR_INVALID_ARGUMENTS, "'PIN CHANGE' failed");

	if (data->pin1.data && data->pin1.len)
		memcpy(ffs1, data->pin1.data, data->pin1.len);

	pin_cmd.flags |= SC_PIN_CMD_NEED_PADDING;

	sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0x24, 0x00, pin_reference);
	apdu.lc = OBERTHUR_AUTH_MAX_LENGTH_PIN * 2;
	apdu.datalen = OBERTHUR_AUTH_MAX_LENGTH_PIN * 2;
	apdu.data = ffs1;

	pin_cmd.apdu = &apdu;
	pin_cmd.pin_type = SC_AC_CHV;
	pin_cmd.cmd = SC_PIN_CMD_CHANGE;
	pin_cmd.flags |= SC_PIN_CMD_USE_PINPAD;
	pin_cmd.pin_reference = pin_reference;
	if (pin_cmd.pin1.min_length < 4)
		pin_cmd.pin1.min_length = 4;
	pin_cmd.pin1.max_length = 8;
	pin_cmd.pin1.encoding = SC_PIN_ENCODING_ASCII;
	pin_cmd.pin1.offset = 5 + OBERTHUR_AUTH_MAX_LENGTH_PIN;
	pin_cmd.pin1.data = ffs1;
	pin_cmd.pin1.len = OBERTHUR_AUTH_MAX_LENGTH_PIN;
	pin_cmd.pin1.pad_length = 0;

	memcpy(&pin_cmd.pin2, &pin_cmd.pin1, sizeof(pin_cmd.pin2));
	pin_cmd.pin1.offset = 5;
	pin_cmd.pin2.data = ffs2;

	rv = iso_drv->ops->pin_cmd(card, &pin_cmd, tries_left);
	LOG_TEST_RET(card->ctx, rv, "PIN CMD 'VERIFY' with pinpad failed");

	LOG_FUNC_RETURN(card->ctx, rv);
}
