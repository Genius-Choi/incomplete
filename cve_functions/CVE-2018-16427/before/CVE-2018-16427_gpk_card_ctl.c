gpk_card_ctl(sc_card_t *card, unsigned long cmd, void *ptr)
{
	switch (cmd) {
	case SC_CARDCTL_ERASE_CARD:
		return gpk_erase_card(card);
	case SC_CARDCTL_GET_DEFAULT_KEY:
		return gpk_get_default_key(card,
				(struct sc_cardctl_default_key *) ptr);
	case SC_CARDCTL_GPK_VARIANT:
		*(int *) ptr = card->type;
		return 0;
	case SC_CARDCTL_GPK_LOCK:
		return gpk_lock(card, (struct sc_cardctl_gpk_lock *) ptr);
	case SC_CARDCTL_GPK_PKINIT:
		return gpk_pkfile_init(card,
			       (struct sc_cardctl_gpk_pkinit *) ptr);
	case SC_CARDCTL_GPK_PKLOAD:
		return gpk_pkfile_load(card,
			       (struct sc_cardctl_gpk_pkload *) ptr);
	case SC_CARDCTL_GPK_IS_LOCKED:
		*(int *) ptr = DRVDATA(card)->locked;
		return 0;
	case SC_CARDCTL_GPK_GENERATE_KEY:
		return gpk_generate_key(card,
				(struct sc_cardctl_gpk_genkey *) ptr);
	case SC_CARDCTL_GET_SERIALNR:
		return gpk_get_serialnr(card, (sc_serial_number_t *) ptr);
	}


	return SC_ERROR_NOT_SUPPORTED;
}
