static int asepcos_match_card(sc_card_t *card)
{
	int i = _sc_match_atr(card, asepcos_atrs, &card->type);
	if (i < 0)
		return 0;
	return 1;
}
