static int itacns_add_pin(sc_pkcs15_card_t *p15card,
	char *label,
	int id,
	int auth_id,
	int reference,
	sc_path_t *path,
	int flags)
{
	struct sc_pkcs15_auth_info pin_info;
	struct sc_pkcs15_object pin_obj;

	SC_FUNC_CALLED(p15card->card->ctx, 1);

	memset(&pin_info, 0, sizeof(pin_info));
	pin_info.auth_type = SC_PKCS15_PIN_AUTH_TYPE_PIN;
	pin_info.auth_id.len = 1;
	pin_info.auth_id.value[0] = id;
	pin_info.attrs.pin.reference = reference;
	pin_info.attrs.pin.flags = flags;
	pin_info.attrs.pin.type = SC_PKCS15_PIN_TYPE_ASCII_NUMERIC;
	pin_info.attrs.pin.min_length = 5;
	pin_info.attrs.pin.stored_length = 8;
	pin_info.attrs.pin.max_length = 8;
	pin_info.attrs.pin.pad_char = 0xff;
	pin_info.logged_in = SC_PIN_STATE_UNKNOWN;
	if(path)
        pin_info.path = *path;

	memset(&pin_obj, 0, sizeof(pin_obj));
	strlcpy(pin_obj.label, label, sizeof(pin_obj.label));
	pin_obj.flags = SC_PKCS15_CO_FLAG_PRIVATE |
		(auth_id ? SC_PKCS15_CO_FLAG_MODIFIABLE : 0);
	if (auth_id) {
		pin_obj.auth_id.len = 1;
		pin_obj.auth_id.value[0] = auth_id;
	} else
		pin_obj.auth_id.len = 0;

	return sc_pkcs15emu_add_pin_obj(p15card, &pin_obj, &pin_info);
}
