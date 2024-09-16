auth_update_key(struct sc_card *card, struct sc_cardctl_oberthur_updatekey_info *info)
{
	int rv, ii;

	LOG_FUNC_CALLED(card->ctx);

	if (info->data_len != sizeof(void *) || !info->data)
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_INVALID_ARGUMENTS);

	if (info->type == SC_CARDCTL_OBERTHUR_KEY_RSA_CRT)   {
		struct sc_pkcs15_prkey_rsa  *rsa = (struct sc_pkcs15_prkey_rsa *)info->data;
		struct sc_pkcs15_bignum bn[5];

		sc_log(card->ctx, "Import RSA CRT");
		bn[0] = rsa->p;
		bn[1] = rsa->q;
		bn[2] = rsa->iqmp;
		bn[3] = rsa->dmp1;
		bn[4] = rsa->dmq1;
		for (ii=0;ii<5;ii++)   {
			struct auth_update_component_info args;

			memset(&args, 0, sizeof(args));
			args.type = SC_CARDCTL_OBERTHUR_KEY_RSA_CRT;
			args.component = ii+1;
			args.data = bn[ii].data;
			args.len = bn[ii].len;

			rv = auth_update_component(card, &args);
			LOG_TEST_RET(card->ctx, rv, "Update RSA component failed");
		}
	}
	else if (info->type == SC_CARDCTL_OBERTHUR_KEY_DES)   {
		rv = SC_ERROR_NOT_SUPPORTED;
	}
	else   {
		rv = SC_ERROR_INVALID_DATA;
	}

	LOG_FUNC_RETURN(card->ctx, rv);
}
