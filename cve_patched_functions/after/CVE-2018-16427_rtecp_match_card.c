static int rtecp_match_card(sc_card_t *card)
{
	int i = -1;
	i = _sc_match_atr(card, rtecp_atrs, &card->type);
	if (i >= 0) {
		card->name = rtecp_atrs[i].name;
		SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_NORMAL, 1);
	}
	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_NORMAL, 0);
}
