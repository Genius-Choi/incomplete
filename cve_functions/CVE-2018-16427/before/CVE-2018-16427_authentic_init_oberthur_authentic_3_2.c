authentic_init_oberthur_authentic_3_2(struct sc_card *card)
{
	struct sc_context *ctx = card->ctx;
	unsigned int flags;
	int rv = 0;

	LOG_FUNC_CALLED(ctx);

	flags = AUTHENTIC_CARD_DEFAULT_FLAGS;

	_sc_card_add_rsa_alg(card, 1024, flags, 0x10001);
	_sc_card_add_rsa_alg(card, 2048, flags, 0x10001);

	card->caps = SC_CARD_CAP_RNG;
	card->caps |= SC_CARD_CAP_APDU_EXT;
	card->caps |= SC_CARD_CAP_USE_FCI_AC;

#ifdef ENABLE_SM
	card->sm_ctx.ops.open = authentic_sm_open;
	card->sm_ctx.ops.get_sm_apdu = authentic_sm_get_wrapped_apdu;
	card->sm_ctx.ops.free_sm_apdu = authentic_sm_free_wrapped_apdu;
#endif

	rv = authentic_select_aid(card, aid_AuthentIC_3_2, sizeof(aid_AuthentIC_3_2), NULL, NULL);
	LOG_TEST_RET(ctx, rv, "AuthentIC application select error");

	rv = authentic_select_mf(card, NULL);
	LOG_TEST_RET(ctx, rv, "MF selection error");

	LOG_FUNC_RETURN(ctx, rv);
}
