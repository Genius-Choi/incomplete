static int loadFile(const sc_pkcs15_card_t *p15card, const sc_path_t *path,
	u8 *buf, const size_t buflen)
{
	int sc_res;
	SC_FUNC_CALLED(p15card->card->ctx, 1);

	sc_res = sc_select_file(p15card->card, path, NULL);
	if(sc_res != SC_SUCCESS)
		return sc_res;

	sc_res = sc_read_binary(p15card->card, 0, buf, buflen, 0);
	return sc_res;
}
