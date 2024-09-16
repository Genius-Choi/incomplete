auth_create_reference_data (struct sc_card *card,
		struct sc_cardctl_oberthur_createpin_info *args)
{
	struct sc_apdu apdu;
	struct sc_pin_cmd_pin pin_info, puk_info;
	int rv, len;
	unsigned char sbuf[SC_MAX_APDU_BUFFER_SIZE];

	LOG_FUNC_CALLED(card->ctx);
	sc_log(card->ctx, "PIN reference %i", args->ref);

	if (args->type != SC_AC_CHV)
		LOG_TEST_RET(card->ctx, SC_ERROR_NOT_SUPPORTED, "Unsupported PIN type");

	if (args->pin_tries < 1 || !args->pin || !args->pin_len)
		LOG_TEST_RET(card->ctx, SC_ERROR_INVALID_ARGUMENTS, "Invalid PIN options");

	if (args->ref != OBERTHUR_PIN_REFERENCE_USER && args->ref != OBERTHUR_PIN_REFERENCE_PUK)
		LOG_TEST_RET(card->ctx, SC_ERROR_INVALID_PIN_REFERENCE, "Invalid PIN reference");

	auth_init_pin_info(card, &puk_info, OBERTHUR_AUTH_TYPE_PUK);
	auth_init_pin_info(card, &pin_info, OBERTHUR_AUTH_TYPE_PIN);

	if (args->puk && args->puk_len && (args->puk_len%puk_info.pad_length))
		LOG_TEST_RET(card->ctx, SC_ERROR_INVALID_ARGUMENTS, "Invalid PUK options");

	len = 0;
	sc_log(card->ctx, "len %i", len);
	sbuf[len++] = args->pin_tries;
	sbuf[len++] = pin_info.pad_length;
	sc_log(card->ctx, "len %i", len);
	memset(sbuf + len, pin_info.pad_char, pin_info.pad_length);
	memcpy(sbuf + len, args->pin, args->pin_len);
	len += pin_info.pad_length;
	sc_log(card->ctx, "len %i", len);

	if (args->puk && args->puk_len)   {
		sbuf[len++] = args->puk_tries;
		sbuf[len++] = args->puk_len / puk_info.pad_length;
		sc_log(card->ctx, "len %i", len);
		memcpy(sbuf + len, args->puk, args->puk_len);
		len += args->puk_len;
	}

	sc_log(card->ctx, "len %i", len);
	sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0x24, 1, args->ref & ~OBERTHUR_PIN_LOCAL);
	apdu.data = sbuf;
	apdu.datalen = len;
	apdu.lc = len;

	rv = sc_transmit_apdu(card, &apdu);
	sc_mem_clear(sbuf, sizeof(sbuf));
	LOG_TEST_RET(card->ctx, rv, "APDU transmit failed");

	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);

	LOG_FUNC_RETURN(card->ctx, rv);
}
