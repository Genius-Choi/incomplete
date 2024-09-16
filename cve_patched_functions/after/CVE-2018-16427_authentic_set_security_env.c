authentic_set_security_env(struct sc_card *card,
		const struct sc_security_env *env, int se_num)
{
	struct sc_context *ctx = card->ctx;
	struct sc_apdu apdu;
	unsigned char cse_crt_dst[] = {
		0x80, 0x01, AUTHENTIC_ALGORITHM_RSA_PKCS1,
		0x83, 0x01, env->key_ref[0] & ~AUTHENTIC_OBJECT_REF_FLAG_LOCAL,
	};
	unsigned char cse_crt_ct[] = {
		0x80, 0x01, AUTHENTIC_ALGORITHM_RSA_PKCS1,
		0x83, 0x01, env->key_ref[0] & ~AUTHENTIC_OBJECT_REF_FLAG_LOCAL,
	};
	int rv;

	LOG_FUNC_CALLED(ctx);
	sc_log(ctx, "set SE#%i(op:0x%X,algo:0x%X,algo_ref:0x%X,flags:0x%X), key_ref:0x%X",
			se_num, env->operation, env->algorithm, env->algorithm_ref, env->algorithm_flags, env->key_ref[0]);
	switch (env->operation)  {
	case SC_SEC_OPERATION_SIGN:
		sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0x22, 0x41, AUTHENTIC_TAG_CRT_DST);
		apdu.data = cse_crt_dst;
		apdu.datalen = sizeof(cse_crt_dst);
		apdu.lc = sizeof(cse_crt_dst);
		break;
	case SC_SEC_OPERATION_DECIPHER:
		sc_format_apdu(card, &apdu, SC_APDU_CASE_3_SHORT, 0x22, 0x41, AUTHENTIC_TAG_CRT_CT);
		apdu.data = cse_crt_ct;
		apdu.datalen = sizeof(cse_crt_ct);
		apdu.lc = sizeof(cse_crt_ct);
		break;
	default:
		LOG_FUNC_RETURN(ctx, SC_ERROR_NOT_SUPPORTED);
	}

	rv = sc_transmit_apdu(card, &apdu);
	LOG_TEST_RET(ctx, rv, "APDU transmit failed");
	rv = sc_check_sw(card, apdu.sw1, apdu.sw2);
	LOG_TEST_RET(ctx, rv, "MSE restore error");

	LOG_FUNC_RETURN(ctx, rv);
}
