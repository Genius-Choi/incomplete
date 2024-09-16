static int itacns_add_prkey(sc_pkcs15_card_t *p15card,
                const sc_pkcs15_id_t *id,
                const char *label,
                int type, unsigned int modulus_length, int usage,
		const sc_path_t *path, int ref,
                const sc_pkcs15_id_t *auth_id, int obj_flags)
{
	sc_pkcs15_prkey_info_t info;
	sc_pkcs15_object_t obj;

	SC_FUNC_CALLED(p15card->card->ctx, 1);

	if(type != SC_PKCS15_TYPE_PRKEY_RSA) {
		sc_debug(p15card->card->ctx, SC_LOG_DEBUG_NORMAL,
			"Cannot add a private key of a type other than RSA");
		return 1;
	}

	memset(&info, 0, sizeof(info));
	memset(&obj,  0, sizeof(obj));

	info.id			= *id;
	info.modulus_length	= modulus_length;
	info.usage		= usage;
	info.native		= 1;
	info.key_reference	= ref;

	if (path)
	        info.path = *path;

	obj.flags = obj_flags;
	strlcpy(obj.label, label, sizeof(obj.label));
	if (auth_id != NULL)
		obj.auth_id = *auth_id;

	return sc_pkcs15emu_add_rsa_prkey(p15card, &obj, &info);
}
