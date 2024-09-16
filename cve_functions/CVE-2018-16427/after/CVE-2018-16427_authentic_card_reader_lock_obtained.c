static int authentic_card_reader_lock_obtained(sc_card_t *card, int was_reset)
{
	int r = SC_SUCCESS;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	if (was_reset > 0
			&& card->type == SC_CARD_TYPE_OBERTHUR_AUTHENTIC_3_2) {
		r = authentic_select_aid(card, aid_AuthentIC_3_2, sizeof(aid_AuthentIC_3_2), NULL, NULL);
	}

	LOG_FUNC_RETURN(card->ctx, r);
}
