authentic_init(struct sc_card *card)
{
	struct sc_context *ctx = card->ctx;
	int ii, rv = SC_ERROR_INVALID_CARD;

	LOG_FUNC_CALLED(ctx);
	for(ii=0;authentic_known_atrs[ii].atr;ii++)   {
		if (card->type == authentic_known_atrs[ii].type)   {
			card->name = authentic_known_atrs[ii].name;
			card->flags = authentic_known_atrs[ii].flags;
			break;
		}
	}

	if (!authentic_known_atrs[ii].atr)
		LOG_FUNC_RETURN(ctx, SC_ERROR_INVALID_CARD);

	card->cla  = 0x00;
	card->drv_data = (struct authentic_private_data *) calloc(sizeof(struct authentic_private_data), 1);
	if (!card->drv_data)
		LOG_FUNC_RETURN(ctx, SC_ERROR_OUT_OF_MEMORY);

	if (card->type == SC_CARD_TYPE_OBERTHUR_AUTHENTIC_3_2)
		rv = authentic_init_oberthur_authentic_3_2(card);

	if (rv != SC_SUCCESS)
		rv = authentic_get_serialnr(card, NULL);

	if (rv != SC_SUCCESS)
		rv = SC_ERROR_INVALID_CARD;

	LOG_FUNC_RETURN(ctx, rv);
}
