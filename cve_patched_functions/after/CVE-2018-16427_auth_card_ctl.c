auth_card_ctl(struct sc_card *card, unsigned long cmd, void *ptr)
{
	switch (cmd) {
	case SC_CARDCTL_GET_DEFAULT_KEY:
		return auth_get_default_key(card,
				(struct sc_cardctl_default_key *) ptr);
	case SC_CARDCTL_OBERTHUR_GENERATE_KEY:
		return auth_generate_key(card, 0,
				(struct sc_cardctl_oberthur_genkey_info *) ptr);
	case SC_CARDCTL_OBERTHUR_UPDATE_KEY:
		return auth_update_key(card,
				(struct sc_cardctl_oberthur_updatekey_info *) ptr);
	case SC_CARDCTL_OBERTHUR_CREATE_PIN:
		return auth_create_reference_data(card,
				(struct sc_cardctl_oberthur_createpin_info *) ptr);
	case SC_CARDCTL_GET_SERIALNR:
		return auth_get_serialnr(card, (struct sc_serial_number *)ptr);
	case SC_CARDCTL_LIFECYCLE_GET:
	case SC_CARDCTL_LIFECYCLE_SET:
		return SC_ERROR_NOT_SUPPORTED;
	default:
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_NOT_SUPPORTED);
	}
}
