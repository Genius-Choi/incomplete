auth_finish(struct sc_card *card)
{
	free(card->drv_data);
	return SC_SUCCESS;
}
