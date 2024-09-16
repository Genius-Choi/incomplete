auth_init_pin_info(struct sc_card *card, struct sc_pin_cmd_pin *pin,
		unsigned int type)
{
	pin->offset = 0;
	pin->pad_char   = 0xFF;
	pin->encoding   = SC_PIN_ENCODING_ASCII;

	if (type == OBERTHUR_AUTH_TYPE_PIN)   {
		pin->max_length = OBERTHUR_AUTH_MAX_LENGTH_PIN;
		pin->pad_length = OBERTHUR_AUTH_MAX_LENGTH_PIN;
	}
	else    {
		pin->max_length = OBERTHUR_AUTH_MAX_LENGTH_PUK;
		pin->pad_length = OBERTHUR_AUTH_MAX_LENGTH_PUK;
	}
}
