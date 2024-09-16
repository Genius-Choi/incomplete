auth_pin_reset_oberthur_style(struct sc_card *card, unsigned int type,
		struct sc_pin_cmd_data *data, int *tries_left)
{
	struct sc_card_driver *iso_drv = sc_get_iso7816_driver();
	struct sc_pin_cmd_data pin_cmd;
	struct sc_path tmp_path;
	struct sc_file *tmp_file = NULL;
	struct sc_apdu apdu;
	unsigned char puk[OBERTHUR_AUTH_MAX_LENGTH_PUK];
	unsigned char ffs1[0x100];
	int rv, rvv, local_pin_reference;

	LOG_FUNC_CALLED(card->ctx);

	local_pin_reference = data->pin_reference & ~OBERTHUR_PIN_LOCAL;

	if (data->pin_reference !=  OBERTHUR_PIN_REFERENCE_USER)
		LOG_TEST_RET(card->ctx, SC_ERROR_INVALID_ARGUMENTS, "Oberthur style 'PIN RESET' failed: invalid PIN reference");

	memset(&pin_cmd, 0, sizeof(pin_cmd));
	memset(&tmp_path, 0, sizeof(struct sc_path));

	pin_cmd.pin_type = SC_AC_CHV;
	pin_cmd.cmd = SC_PIN_CMD_VERIFY;
	pin_cmd.pin_reference = OBERTHUR_PIN_REFERENCE_PUK;
	memcpy(&pin_cmd.pin1, &data->pin1, sizeof(pin_cmd.pin1));

	rv = auth_pin_verify(card, SC_AC_CHV, &pin_cmd, tries_left);
	LOG_TEST_RET(card->ctx, rv, "Oberthur style 'PIN RESET' failed: SOPIN verify error");

	sc_format_path("2000", &tmp_path);
	tmp_path.type = SC_PATH_TYPE_FILE_ID;
	rv = iso_ops->select_file(card, &tmp_path, &tmp_file);
	LOG_TEST_RET(card->ctx, rv, "select PUK file");

	if (!tmp_file || tmp_file->size < OBERTHUR_AUTH_MAX_LENGTH_PUK)
		LOG_TEST_RET(card->ctx, SC_ERROR_FILE_TOO_SMALL, "Oberthur style 'PIN RESET' failed");

	rv = iso_ops->read_binary(card, 0, puk, OBERTHUR_AUTH_MAX_LENGTH_PUK, 0);
	LOG_TEST_RET(card->ctx, rv, "read PUK file error");
	if (rv != OBERTHUR_AUTH_MAX_LENGTH_PUK)
		LOG_TEST_RET(card->ctx, SC_ERROR_INVALID_DATA, "Oberthur style 'PIN RESET' failed");

	memset(ffs1, 0xFF, sizeof(ffs1));
	memcpy(ffs1, puk, rv);

	memset(&pin_cmd, 0, sizeof(pin_cmd));
	pin_cmd.pin_type = SC_AC_CHV;
        pin_cmd.cmd = SC_PIN_CMD_UNBLOCK;
	pin_cmd.pin_reference = local_pin_reference;
	auth_init_pin_info(card, &pin_cmd.pin1, OBERTHUR_AUTH_TYPE_PUK);
	pin_cmd.pin1.data = ffs1;
	pin_cmd.pin1.len = OBERTHUR_AUTH_MAX_LENGTH_PUK;

	if (data->pin2.data)   {
		memcpy(&pin_cmd.pin2, &data->pin2, sizeof(pin_cmd.pin2));
		rv = auth_pin_reset(card, SC_AC_CHV, &pin_cmd, tries_left);
		LOG_FUNC_RETURN(card->ctx, rv);
	}

	sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0x2C, 0x00, local_pin_reference);
	apdu.lc = OBERTHUR_AUTH_MAX_LENGTH_PIN  + OBERTHUR_AUTH_MAX_LENGTH_PUK;
	apdu.datalen = OBERTHUR_AUTH_MAX_LENGTH_PIN  + OBERTHUR_AUTH_MAX_LENGTH_PUK;
	apdu.data = ffs1;

	pin_cmd.apdu = &apdu;
	pin_cmd.flags |= SC_PIN_CMD_USE_PINPAD | SC_PIN_CMD_IMPLICIT_CHANGE;

	pin_cmd.pin1.min_length = 4;
	pin_cmd.pin1.max_length = 8;
	pin_cmd.pin1.encoding = SC_PIN_ENCODING_ASCII;
	pin_cmd.pin1.offset = 5;

	pin_cmd.pin2.data = &ffs1[OBERTHUR_AUTH_MAX_LENGTH_PUK];
	pin_cmd.pin2.len = OBERTHUR_AUTH_MAX_LENGTH_PIN;
	pin_cmd.pin2.offset = 5 + OBERTHUR_AUTH_MAX_LENGTH_PUK;
	pin_cmd.pin2.min_length = 4;
	pin_cmd.pin2.max_length = 8;
	pin_cmd.pin2.encoding = SC_PIN_ENCODING_ASCII;

	rvv = iso_drv->ops->pin_cmd(card, &pin_cmd, tries_left);
	if (rvv)
		sc_log(card->ctx,
				"%s: PIN CMD 'VERIFY' with pinpad failed",
				sc_strerror(rvv));

	if (auth_current_ef)
		rv = iso_ops->select_file(card, &auth_current_ef->path, &auth_current_ef);

	if (rv > 0)
		rv = 0;

	LOG_FUNC_RETURN(card->ctx, rv ? rv: rvv);
}
