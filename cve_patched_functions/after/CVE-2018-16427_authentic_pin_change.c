authentic_pin_change(struct sc_card *card, struct sc_pin_cmd_data *data, int *tries_left)
{
	struct sc_context *ctx = card->ctx;
	struct authentic_private_data *prv_data = (struct authentic_private_data *) card->drv_data;
	struct sc_apdu apdu;
	unsigned char pin_data[SC_MAX_APDU_BUFFER_SIZE];
	size_t offs;
	int rv;

	rv = authentic_pin_get_policy(card, data);
	LOG_TEST_RET(ctx, rv, "Get 'PIN policy' error");

	memset(prv_data->pins_sha1[data->pin_reference], 0, sizeof(prv_data->pins_sha1[0]));

	if (!data->pin1.data && !data->pin1.len && !data->pin2.data && !data->pin2.len)   {
		if (!(card->reader->capabilities & SC_READER_CAP_PIN_PAD))
			LOG_TEST_RET(ctx, SC_ERROR_NOT_SUPPORTED, "PIN pad not supported");
		rv = authentic_pin_change_pinpad(card, data->pin_reference, tries_left);
		sc_log(ctx, "authentic_pin_cmd(SC_PIN_CMD_CHANGE) chv_change_pinpad returned %i", rv);
		LOG_FUNC_RETURN(ctx, rv);
	}

	if (card->max_send_size && (data->pin1.len + data->pin2.len > (int)card->max_send_size))
		LOG_TEST_RET(ctx, SC_ERROR_INVALID_PIN_LENGTH, "APDU transmit failed");

	memset(pin_data, data->pin1.pad_char, sizeof(pin_data));
	offs = 0;
	if (data->pin1.data && data->pin1.len)   {
		memcpy(pin_data, data->pin1.data, data->pin1.len);
		offs += data->pin1.pad_length;
	}
	if (data->pin2.data && data->pin2.len)
		memcpy(pin_data + offs, data->pin2.data, data->pin2.len);

	sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0x24, offs ? 0x00 : 0x01, data->pin_reference);
	apdu.data = pin_data;
	apdu.datalen = offs + data->pin1.pad_length;
	apdu.lc = offs + data->pin1.pad_length;

	rv = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(ctx, rv, "APDU transmit failed");
	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);

	LOG_FUNC_RETURN(ctx, rv);
}
