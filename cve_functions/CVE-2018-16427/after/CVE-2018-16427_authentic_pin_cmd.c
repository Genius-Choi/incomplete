authentic_pin_cmd(struct sc_card *card, struct sc_pin_cmd_data *data, int *tries_left)
{
	struct sc_context *ctx = card->ctx;
	int rv = SC_ERROR_INTERNAL;

	LOG_FUNC_CALLED(ctx);
	sc_log(ctx, "PIN-CMD:%X,PIN(type:%X,ret:%i)", data->cmd, data->pin_type, data->pin_reference);
	sc_log(ctx, "PIN1(%p,len:%i,tries-left:%i)", data->pin1.data, data->pin1.len, data->pin1.tries_left);
	sc_log(ctx, "PIN2(%p,len:%i)", data->pin2.data, data->pin2.len);

	switch (data->cmd)   {
	case SC_PIN_CMD_VERIFY:
		rv = authentic_pin_verify(card, data);
		break;
	case SC_PIN_CMD_CHANGE:
		rv = authentic_pin_change(card, data, tries_left);
		break;
	case SC_PIN_CMD_UNBLOCK:
		rv = authentic_pin_reset(card, data, tries_left);
		break;
	case SC_PIN_CMD_GET_INFO:
		rv = authentic_pin_get_policy(card, data);
		break;
	default:
		LOG_TEST_RET(ctx, SC_ERROR_NOT_SUPPORTED, "Unsupported PIN command");
	}

	if (rv == SC_ERROR_PIN_CODE_INCORRECT && tries_left)
		*tries_left = data->pin1.tries_left;

	LOG_FUNC_RETURN(ctx, rv);
}
