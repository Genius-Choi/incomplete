static int entersafe_match_card(sc_card_t *card)
{
	int i;
	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	i = _sc_match_atr(card, entersafe_atrs, &card->type);
	if (i < 0)
		return 0;		

	return 1;
}
