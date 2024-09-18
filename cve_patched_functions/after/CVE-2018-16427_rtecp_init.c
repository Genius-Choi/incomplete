static int rtecp_init(sc_card_t *card)
{
	sc_algorithm_info_t info;
	unsigned long flags;

	assert(card && card->ctx);
	card->caps |= SC_CARD_CAP_RNG;
	card->cla = 0;

	flags = SC_ALGORITHM_RSA_RAW | SC_ALGORITHM_ONBOARD_KEY_GEN
		| SC_ALGORITHM_RSA_PAD_NONE | SC_ALGORITHM_RSA_HASH_NONE;

	_sc_card_add_rsa_alg(card, 256, flags, 0);
	_sc_card_add_rsa_alg(card, 512, flags, 0);
	_sc_card_add_rsa_alg(card, 768, flags, 0);
	_sc_card_add_rsa_alg(card, 1024, flags, 0);
	_sc_card_add_rsa_alg(card, 1280, flags, 0);
	_sc_card_add_rsa_alg(card, 1536, flags, 0);
	_sc_card_add_rsa_alg(card, 1792, flags, 0);
	_sc_card_add_rsa_alg(card, 2048, flags, 0);

	memset(&info, 0, sizeof(info));
	info.algorithm = SC_ALGORITHM_GOSTR3410;
	info.key_length = 256;
	info.flags = SC_ALGORITHM_GOSTR3410_RAW | SC_ALGORITHM_ONBOARD_KEY_GEN
		| SC_ALGORITHM_GOSTR3410_HASH_NONE;
	_sc_card_add_algorithm(card, &info);

	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_VERBOSE, 0);
}
