sc_parse_ef_gdo(struct sc_card *card,
		unsigned char *iccsn, size_t *iccsn_len,
		unsigned char *chn, size_t *chn_len)
{
	struct sc_context *ctx;
	struct sc_path path;
	struct sc_file *file;
	unsigned char *gdo = NULL;
	size_t gdo_len = 0;
	int r;

	if (!card)
		return SC_ERROR_INVALID_ARGUMENTS;

	ctx = card->ctx;

	LOG_FUNC_CALLED(ctx);

	sc_format_path("3F002F02", &path);
	r = sc_select_file(card, &path, &file);
	LOG_TEST_GOTO_ERR(ctx, r, "Cannot select EF(GDO) file");

	if (file->size) {
		gdo_len = file->size;
	} else {
		gdo_len = 64;
	}
	gdo = malloc(gdo_len);
	if (!gdo) {
		r = SC_ERROR_OUT_OF_MEMORY;
		goto err;
	}

	r = sc_read_binary(card, 0, gdo, gdo_len, 0);
	LOG_TEST_GOTO_ERR(ctx, r, "Cannot read EF(GDO) file");

	r = sc_parse_ef_gdo_content(gdo, r, iccsn, iccsn_len, chn, chn_len);

err:
	sc_file_free(file);
	free(gdo);

	LOG_FUNC_RETURN(ctx, r);
}
