static int cac_finish(sc_card_t *card)
{
	cac_private_data_t * priv = CAC_DATA(card);

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);
	if (priv) {
		cac_free_private_data(priv);
	}
	return SC_SUCCESS;
}
