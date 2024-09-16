auth_pin_cmd(struct sc_card *card, struct sc_pin_cmd_data *data, int *tries_left)
{
	int rv = SC_ERROR_INTERNAL;

	LOG_FUNC_CALLED(card->ctx);
	if (data->pin_type != SC_AC_CHV)
		LOG_TEST_RET(card->ctx, SC_ERROR_NOT_SUPPORTED, "auth_pin_cmd() unsupported PIN type");

	sc_log(card->ctx, "PIN CMD:%i; reference:%i; pin1:%p/%i, pin2:%p/%i", data->cmd,
			data->pin_reference, data->pin1.data, data->pin1.len,
			data->pin2.data, data->pin2.len);
	switch (data->cmd) {
	case SC_PIN_CMD_VERIFY:
		rv = auth_pin_verify(card, SC_AC_CHV, data, tries_left);
		LOG_TEST_RET(card->ctx, rv, "CMD 'PIN VERIFY' failed");
		break;
	case SC_PIN_CMD_CHANGE:
		rv = auth_pin_change(card, SC_AC_CHV, data, tries_left);
		LOG_TEST_RET(card->ctx, rv, "CMD 'PIN VERIFY' failed");
		break;
	case SC_PIN_CMD_UNBLOCK:
		rv = auth_pin_reset(card, SC_AC_CHV, data, tries_left);
		LOG_TEST_RET(card->ctx, rv, "CMD 'PIN VERIFY' failed");
		break;
	default:
		LOG_TEST_RET(card->ctx, SC_ERROR_NOT_SUPPORTED, "Unsupported PIN operation");
	}

	LOG_FUNC_RETURN(card->ctx, rv);
}
