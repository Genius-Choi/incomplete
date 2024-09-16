auth_generate_key(struct sc_card *card, int use_sm,
		struct sc_cardctl_oberthur_genkey_info *data)
{
	struct sc_apdu apdu;
	unsigned char sbuf[SC_MAX_APDU_BUFFER_SIZE];
	struct sc_path tmp_path;
	int rv = 0;

	LOG_FUNC_CALLED(card->ctx);
	if (data->key_bits < 512 || data->key_bits > 2048 ||
			(data->key_bits%0x20)!=0)   {
		LOG_TEST_RET(card->ctx, SC_ERROR_INVALID_ARGUMENTS, "Illegal key length");
	}

	sbuf[0] = (data->id_pub >> 8) & 0xFF;
	sbuf[1] = data->id_pub & 0xFF;
	sbuf[2] = (data->id_prv >> 8) & 0xFF;
	sbuf[3] = data->id_prv & 0xFF;
	if (data->exponent != 0x10001)   {
		rv = auth_encode_exponent(data->exponent, &sbuf[5],SC_MAX_APDU_BUFFER_SIZE-6);
		LOG_TEST_RET(card->ctx, rv, "Cannot encode exponent");

		sbuf[4] = rv;
		rv++;
	}

	sc_format_apdu(card, &apdu, SC_APDU_CASE_4_SHORT, 0x46, 0x00, 0x00);
	apdu.resp = calloc(1, data->key_bits/8+8);
	if (!apdu.resp)
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_OUT_OF_MEMORY);

	apdu.resplen = data->key_bits/8+8;
	apdu.lc = rv + 4;
	apdu.le = data->key_bits/8;
	apdu.data = sbuf;
	apdu.datalen = rv + 4;

	rv = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(card->ctx, rv, "APDU transmit failed");
	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
	LOG_TEST_RET(card->ctx, rv, "Card returned error");

	memset(&tmp_path, 0, sizeof(struct sc_path));
	tmp_path.type = SC_PATH_TYPE_FILE_ID;
	tmp_path.len = 2;
	memcpy(tmp_path.value, sbuf, 2);

	rv = auth_select_file(card, &tmp_path, NULL);
	LOG_TEST_RET(card->ctx, rv, "cannot select public key");

	rv = auth_read_component(card, SC_CARDCTL_OBERTHUR_KEY_RSA_PUBLIC,
			1, apdu.resp, data->key_bits/8);
	LOG_TEST_RET(card->ctx, rv, "auth_read_component() returned error");

	apdu.resplen = rv;

	if (data->pubkey)   {
		if (data->pubkey_len < apdu.resplen)
			LOG_FUNC_RETURN(card->ctx, SC_ERROR_INVALID_ARGUMENTS);

		memcpy(data->pubkey,apdu.resp,apdu.resplen);
	}

	data->pubkey_len = apdu.resplen;
	free(apdu.resp);

	sc_log(card->ctx, "resulted public key len %"SC_FORMAT_LEN_SIZE_T"u",
	       apdu.resplen);
	LOG_FUNC_RETURN(card->ctx, SC_SUCCESS);
}
