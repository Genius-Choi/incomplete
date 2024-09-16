static int entersafe_card_ctl_2048(sc_card_t *card, unsigned long cmd, void *ptr)
{
	sc_entersafe_create_data *tmp = (sc_entersafe_create_data *)ptr;

	SC_FUNC_CALLED(card->ctx, SC_LOG_DEBUG_VERBOSE);

	switch (cmd)
	{
	case SC_CARDCTL_ENTERSAFE_CREATE_FILE:
		if (tmp->type == SC_ENTERSAFE_MF_DATA)
			return entersafe_create_mf(card, tmp);
		else if (tmp->type == SC_ENTERSAFE_DF_DATA)
			return entersafe_create_df(card, tmp);
		else if (tmp->type == SC_ENTERSAFE_EF_DATA)
			return entersafe_create_ef(card, tmp);
		else
			return SC_ERROR_INTERNAL;
	case SC_CARDCTL_ENTERSAFE_WRITE_KEY:
		return entersafe_write_key(card, (sc_entersafe_wkey_data *)ptr);
	case SC_CARDCTL_ENTERSAFE_GENERATE_KEY:
		return entersafe_gen_key(card, (sc_entersafe_gen_key_data *)ptr);
	case SC_CARDCTL_ERASE_CARD:
		return entersafe_erase_card(card);
	case SC_CARDCTL_GET_SERIALNR:
		return entersafe_get_serialnr(card, (sc_serial_number_t *)ptr);
	case SC_CARDCTL_ENTERSAFE_PREINSTALL_KEYS:
		 return entersafe_preinstall_keys(card,entersafe_preinstall_rsa_2048);
	default:
		return SC_ERROR_NOT_SUPPORTED;
	}
}
