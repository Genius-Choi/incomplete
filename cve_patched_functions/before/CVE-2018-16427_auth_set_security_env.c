auth_set_security_env(struct sc_card *card,
		const struct sc_security_env *env, int se_num)
{
	struct auth_senv *auth_senv = &((struct auth_private_data *) card->drv_data)->senv;
	struct sc_apdu apdu;
	long unsigned pads = env->algorithm_flags & SC_ALGORITHM_RSA_PADS;
	long unsigned supported_pads = SC_ALGORITHM_RSA_PAD_PKCS1 | SC_ALGORITHM_RSA_PAD_ISO9796;
	int rv;
	unsigned char rsa_sbuf[3] = {
		0x80, 0x01, 0xFF
	};
	unsigned char des_sbuf[13] = {
		0x80, 0x01, 0x01,
		0x87, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
	};

	LOG_FUNC_CALLED(card->ctx);
	sc_log(card->ctx,
	       "op %i; path %s; key_ref 0x%X; algos 0x%X; flags 0x%lX",
	       env->operation, sc_print_path(&env->file_ref), env->key_ref[0],
	       env->algorithm_flags, env->flags);

	memset(auth_senv, 0, sizeof(struct auth_senv));

	if (!(env->flags & SC_SEC_ENV_FILE_REF_PRESENT))
		LOG_TEST_RET(card->ctx, SC_ERROR_INTERNAL, "Key file is not selected.");

	switch (env->algorithm)   {
	case SC_ALGORITHM_DES:
	case SC_ALGORITHM_3DES:
		sc_log(card->ctx,
		       "algo SC_ALGORITHM_xDES: ref %X, flags %lX",
		       env->algorithm_ref, env->flags);

		if (env->operation == SC_SEC_OPERATION_DECIPHER)   {
			sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0x22, 0x41, 0xB8);
			apdu.lc = 3;
			apdu.data = des_sbuf;
			apdu.datalen = 3;
		}
		else {
			sc_log(card->ctx, "Invalid crypto operation: %X", env->operation);
			LOG_TEST_RET(card->ctx, SC_ERROR_NOT_SUPPORTED, "Invalid crypto operation");
		}

		break;
	case SC_ALGORITHM_RSA:
		sc_log(card->ctx, "algo SC_ALGORITHM_RSA");
		if (env->algorithm_flags & SC_ALGORITHM_RSA_HASHES) {
			LOG_TEST_RET(card->ctx, SC_ERROR_NOT_SUPPORTED, "No support for hashes.");
		}

		if (pads & (~supported_pads))   {
			sc_log(card->ctx, "No support for PAD %lX", pads);
			LOG_TEST_RET(card->ctx, SC_ERROR_NOT_SUPPORTED, "No padding support.");
		}

		if (env->operation == SC_SEC_OPERATION_SIGN)   {
			rsa_sbuf[2] = 0x11;

			sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0x22, 0x41, 0xB6);
			apdu.lc = sizeof(rsa_sbuf);
			apdu.datalen = sizeof(rsa_sbuf);
			apdu.data = rsa_sbuf;
		}
		else if (env->operation == SC_SEC_OPERATION_DECIPHER)   {
			rsa_sbuf[2] = 0x11;

			sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0x22, 0x41, 0xB8);
			apdu.lc = sizeof(rsa_sbuf);
			apdu.datalen = sizeof(rsa_sbuf);
			apdu.data = rsa_sbuf;
		}
		else {
			sc_log(card->ctx, "Invalid crypto operation: %X", env->operation);
			LOG_FUNC_RETURN(card->ctx, SC_ERROR_NOT_SUPPORTED);
		}

		break;
	default:
		LOG_TEST_RET(card->ctx, SC_ERROR_NOT_SUPPORTED, "Invalid crypto algorithm supplied");
	}

	rv = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(card->ctx, rv, "APDU transmit failed");
	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
	LOG_TEST_RET(card->ctx, rv, "Card returned error");

	auth_senv->algorithm = env->algorithm;

	LOG_FUNC_RETURN(card->ctx, rv);
}
