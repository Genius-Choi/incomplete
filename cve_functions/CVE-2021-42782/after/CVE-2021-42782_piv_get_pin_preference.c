static int piv_get_pin_preference(sc_card_t *card, int *ptr)
{
	piv_private_data_t * priv = PIV_DATA(card);

	*ptr = priv->pin_preference;
	LOG_FUNC_RETURN(card->ctx, SC_SUCCESS);
}
