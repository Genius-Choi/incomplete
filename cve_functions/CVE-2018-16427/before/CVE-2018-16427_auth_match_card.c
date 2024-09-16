auth_match_card(struct sc_card *card)
{
	if (_sc_match_atr(card, oberthur_atrs, &card->type) < 0)
		return 0;
	else
		return 1;
}
