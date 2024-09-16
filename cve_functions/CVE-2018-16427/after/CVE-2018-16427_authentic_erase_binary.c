authentic_erase_binary(struct sc_card *card, unsigned int offs, size_t count, unsigned long flags)
{
	struct sc_context *ctx = card->ctx;
	int rv;
	unsigned char *buf_zero = NULL;

	LOG_FUNC_CALLED(ctx);
	if (!count)
		LOG_TEST_RET(ctx, SC_ERROR_NOT_SUPPORTED, "'ERASE BINARY' with ZERO count not supported");

	if (card->cache.valid && card->cache.current_ef)
		sc_log(ctx, "current_ef(type=%i) %s", card->cache.current_ef->path.type,
				sc_print_path(&card->cache.current_ef->path));

	buf_zero = calloc(1, count);
	if (!buf_zero)
		LOG_TEST_RET(ctx, SC_ERROR_OUT_OF_MEMORY, "cannot allocate buff 'zero'");

	rv = sc_update_binary(card, offs, buf_zero, count, flags);
	free(buf_zero);
	LOG_TEST_RET(ctx, rv, "'ERASE BINARY' failed");

	LOG_FUNC_RETURN(ctx, SC_SUCCESS);
}
