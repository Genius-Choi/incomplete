auth_init(struct sc_card *card)
{
	struct auth_private_data *data;
	struct sc_path path;
	unsigned long flags;
	int rv = 0;

	data = calloc(1, sizeof(struct auth_private_data));
	if (!data)
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_OUT_OF_MEMORY);

	card->cla = 0x00;
	card->drv_data = data;

	card->caps |= SC_CARD_CAP_RNG;
	card->caps |= SC_CARD_CAP_USE_FCI_AC;

	if (auth_select_aid(card))   {
		sc_log(card->ctx, "Failed to initialize %s", card->name);
		LOG_TEST_RET(card->ctx, SC_ERROR_INVALID_CARD, "Failed to initialize");
	}

	flags = SC_ALGORITHM_RSA_PAD_PKCS1 | SC_ALGORITHM_RSA_PAD_ISO9796;
	flags |= SC_ALGORITHM_RSA_HASH_NONE;
	flags |= SC_ALGORITHM_ONBOARD_KEY_GEN;

	_sc_card_add_rsa_alg(card, 512, flags, 0);
	_sc_card_add_rsa_alg(card, 1024, flags, 0);
	_sc_card_add_rsa_alg(card, 2048, flags, 0);

	sc_format_path("3F00", &path);
	rv = auth_select_file(card, &path, NULL);

	LOG_FUNC_RETURN(card->ctx, rv);
}
