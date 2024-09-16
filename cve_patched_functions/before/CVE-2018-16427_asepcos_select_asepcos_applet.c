static int asepcos_select_asepcos_applet(sc_card_t *card)
{
	static const u8 asepcos_aid[] = {0xA0,0x00,0x00,0x01,0x64,0x41,0x53,0x45,0x50,0x43,0x4F,0x53,0x00};
	sc_path_t tpath;
	int       r;

	memset(&tpath, 0, sizeof(sc_path_t));

	tpath.type = SC_PATH_TYPE_DF_NAME;
	tpath.len  = sizeof(asepcos_aid);
	memcpy(tpath.value, asepcos_aid, sizeof(asepcos_aid));

	r = sc_select_file(card, &tpath, NULL);
	if (r != SC_SUCCESS) {
		sc_debug(card->ctx, SC_LOG_DEBUG_NORMAL, "unable to select ASEPCOS applet");
		return r;
	}

	return SC_SUCCESS;
}
