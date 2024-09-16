gpk_finish(sc_card_t *card)
{
	if (card->drv_data)
		free(card->drv_data);
	card->drv_data = NULL;
	return 0;
}
