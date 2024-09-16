pgp_get_challenge(struct sc_card *card, u8 *rnd, size_t len)
{
	struct pgp_priv_data *priv;

	LOG_FUNC_CALLED(card->ctx);

	priv = DRVDATA(card);
	if (0 == (priv->ext_caps & EXT_CAP_GET_CHALLENGE)) {
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_NOT_SUPPORTED);
	}

	if (priv->max_challenge_size > 0 && len > priv->max_challenge_size) {
		len = priv->max_challenge_size;
	}

	LOG_FUNC_RETURN(card->ctx, iso_ops->get_challenge(card, rnd, len));
}
