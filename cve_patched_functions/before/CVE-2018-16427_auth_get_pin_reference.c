auth_get_pin_reference (struct sc_card *card, int type, int reference, int cmd, int *out_ref)
{
	if (!out_ref)
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_INVALID_ARGUMENTS);

	switch (type) {
	case SC_AC_CHV:
		if (reference != 1 && reference != 2 && reference != 4)
			LOG_FUNC_RETURN(card->ctx, SC_ERROR_INVALID_PIN_REFERENCE);

		*out_ref = reference;
		if (reference == 1 || reference == 4)
			if (cmd == SC_PIN_CMD_VERIFY)
				*out_ref |= 0x80;
		break;

	default:
		LOG_FUNC_RETURN(card->ctx, SC_ERROR_INVALID_ARGUMENTS);
	}

	LOG_FUNC_RETURN(card->ctx, SC_SUCCESS);
}
