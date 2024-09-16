static int coolkey_get_serial_nr_from_CUID(sc_card_t* card, sc_serial_number_t* serial)
{
	coolkey_private_data_t * priv = COOLKEY_DATA(card);

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_NORMAL);
	memcpy(serial->value, &priv->cuid, sizeof(priv->cuid));
	serial->len = sizeof(priv->cuid);
	SC_FUNC_RETURN(card->ctx, SC_LOG_DEBUG_NORMAL, SC_SUCCESS);
}
