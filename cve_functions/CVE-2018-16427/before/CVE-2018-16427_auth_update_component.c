auth_update_component(struct sc_card *card, struct auth_update_component_info *args)
{
	struct sc_apdu apdu;
	unsigned char sbuf[SC_MAX_APDU_BUFFER_SIZE + 0x10];
	unsigned char ins, p1, p2;
	int rv, len;

	LOG_FUNC_CALLED(card->ctx);
	if (args->len > sizeof(sbuf) || args->len > 0x100)
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_INVALID_ARGUMENTS);

	sc_log(card->ctx, "nn %i; len %i", args->component, args->len);
	ins = 0xD8;
	p1 = args->component;
	p2 = 0x04;
	len = 0;

	sbuf[len++] = args->type;
	sbuf[len++] = args->len;
	memcpy(sbuf + len, args->data, args->len);
	len += args->len;

	if (args->type == SC_CARDCTL_OBERTHUR_KEY_DES)   {
		int outl;
		const unsigned char in[8] = {0,0,0,0,0,0,0,0};
		unsigned char out[8];
		EVP_CIPHER_CTX  * ctx = NULL;

		if (args->len!=8 && args->len!=24)
			LOG_FUNC_RETURN(card->ctx, SC_ERROR_INVALID_ARGUMENTS);

		ctx = EVP_CIPHER_CTX_new();
		if (ctx == NULL) 
		    SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_NORMAL,SC_ERROR_OUT_OF_MEMORY);

		p2 = 0;
		if (args->len == 24)
			EVP_EncryptInit_ex(ctx, EVP_des_ede(), NULL, args->data, NULL);
		else
			EVP_EncryptInit_ex(ctx, EVP_des_ecb(), NULL, args->data, NULL);
		rv = EVP_EncryptUpdate(ctx, out, &outl, in, 8);
		EVP_CIPHER_CTX_free(ctx);
		if (rv == 0) {
			sc_log(card->ctx, "OpenSSL encryption error.");
			LOG_FUNC_RETURN(card->ctx, SC_ERROR_INTERNAL);
		}

		sbuf[len++] = 0x03;
		memcpy(sbuf + len, out, 3);
		len += 3;
	}
	else   {
		sbuf[len++] = 0;
	}

	sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, ins,	p1, p2);
	apdu.cla |= 0x80;
	apdu.data = sbuf;
	apdu.datalen = len;
	apdu.lc = len;
	if (args->len == 0x100)   {
		sbuf[0] = args->type;
		sbuf[1] = 0x20;
		memcpy(sbuf + 2, args->data, 0x20);
		sbuf[0x22] = 0;
		apdu.cla |= 0x10;
		apdu.data = sbuf;
		apdu.datalen = 0x23;
		apdu.lc = 0x23;
		rv = sc_transmit_apdu(card, &apdu);
		apdu.cla &= ~0x10;
		LOG_TEST_RET(card->ctx, rv, "APDU transmit failed");

		sbuf[0] = args->type;
		sbuf[1] = 0xE0;
		memcpy(sbuf + 2, args->data + 0x20, 0xE0);
		sbuf[0xE2] = 0;
		apdu.data = sbuf;
		apdu.datalen = 0xE3;
		apdu.lc = 0xE3;
	}

	rv = sc_transmit_apdu(card, &apdu);
	sc_mem_clear(sbuf, sizeof(sbuf));
	LOG_TEST_RET(card->ctx, rv, "APDU transmit failed");

	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
	LOG_FUNC_RETURN(card->ctx, rv);
}
