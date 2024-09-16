authentic_pin_reset(struct sc_card *card, struct sc_pin_cmd_data *data, int *tries_left)
{
	struct sc_context *ctx = card->ctx;
	struct authentic_private_data *prv_data = (struct authentic_private_data *) card->drv_data;
	struct sc_pin_cmd_data pin_cmd, puk_cmd;
	struct sc_apdu apdu;
	unsigned reference;
	int rv, ii;

	LOG_FUNC_CALLED(ctx);
	sc_log(ctx, "reset PIN (ref:%i,lengths %i/%i)", data->pin_reference, data->pin1.len, data->pin2.len);

	memset(prv_data->pins_sha1[data->pin_reference], 0, sizeof(prv_data->pins_sha1[0]));

	memset(&pin_cmd, 0, sizeof(pin_cmd));
	pin_cmd.pin_reference = data->pin_reference;
	pin_cmd.pin_type = data->pin_type;
	pin_cmd.pin1.tries_left = -1;

	rv = authentic_pin_get_policy(card, &pin_cmd);
	LOG_TEST_RET(ctx, rv, "Get 'PIN policy' error");

	if (pin_cmd.pin1.acls[AUTHENTIC_ACL_NUM_PIN_RESET].method == SC_AC_CHV)   {
		for (ii=0;ii<8;ii++)   {
			unsigned char mask = 0x01 << ii;
			if (pin_cmd.pin1.acls[AUTHENTIC_ACL_NUM_PIN_RESET].key_ref & mask)   {
				memset(&puk_cmd, 0, sizeof(puk_cmd));
				puk_cmd.pin_reference = ii + 1;

				rv = authentic_pin_get_policy(card, &puk_cmd);
				LOG_TEST_RET(ctx, rv, "Get 'PIN policy' error");

				if (puk_cmd.pin_type == SC_AC_CHV)
					break;
			}
		}
		if (ii < 8)   {
			puk_cmd.pin1.data = data->pin1.data;
			puk_cmd.pin1.len = data->pin1.len;

			rv = authentic_pin_verify(card, &puk_cmd);

			if (tries_left && rv == SC_ERROR_PIN_CODE_INCORRECT)
				*tries_left = puk_cmd.pin1.tries_left;

			LOG_TEST_RET(ctx, rv, "Cannot verify PUK");
		}
	}

	reference = data->pin_reference;
	if (data->pin2.len)   {
		unsigned char pin_data[SC_MAX_APDU_BUFFER_SIZE];

		memset(pin_data, pin_cmd.pin1.pad_char, sizeof(pin_data));
		memcpy(pin_data, data->pin2.data, data->pin2.len);

		sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0x2C, 0x02, reference);
		apdu.data = pin_data;
		apdu.datalen = pin_cmd.pin1.pad_length;
		apdu.lc = pin_cmd.pin1.pad_length;

		rv = sc_transmit_apdu(card, &apdu);
		LOG_TEST_RET(ctx, rv, "APDU transmit failed");
		rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
		LOG_TEST_RET(ctx, rv, "PIN cmd failed");
	}
	else if (data->pin2.data) {
		sc_format_apdu(card, &apdu, SC_APDU_CASE_1, 0x2C, 3, reference);

		rv = sc_transmit_apdu(card, &apdu);
		LOG_TEST_RET(ctx, rv, "APDU transmit failed");
		rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
		LOG_TEST_RET(ctx, rv, "PIN cmd failed");
	}
	else   {
		rv = authentic_chv_set_pinpad(card, reference);
		LOG_TEST_RET(ctx, rv, "Failed to set PIN with pin-pad");
	}

	LOG_FUNC_RETURN(ctx, rv);
}
