static int coolkey_match_card(sc_card_t *card)
{
	int r;
	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);
	/* Since we send an APDU, the card's logout function may be called...
	 * however it may be in dirty memory */
	card->ops->logout = NULL;

	r = coolkey_select_applet(card);
	return (r >= SC_SUCCESS);
}
