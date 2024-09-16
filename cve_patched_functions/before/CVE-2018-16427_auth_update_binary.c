auth_update_binary(struct sc_card *card, unsigned int offset,
		const unsigned char *buf, size_t count, unsigned long flags)
{
	int rv = 0;

	LOG_FUNC_CALLED(card->ctx);
	sc_log(card->ctx, "offset %i; count %"SC_FORMAT_LEN_SIZE_T"u", offset,
	       count);
	sc_log(card->ctx, "last selected : magic %X; ef %X",
			auth_current_ef->magic, auth_current_ef->ef_structure);

	if (offset & ~0x7FFF)
		LOG_TEST_RET(card->ctx, SC_ERROR_INVALID_ARGUMENTS, "Invalid file offset");

	if (auth_current_ef->magic==SC_FILE_MAGIC &&
			 auth_current_ef->ef_structure == SC_CARDCTL_OBERTHUR_KEY_RSA_PUBLIC)  {
		rv = write_publickey(card, offset, buf, count);
	}
	else if (auth_current_ef->magic==SC_FILE_MAGIC &&
			auth_current_ef->ef_structure == SC_CARDCTL_OBERTHUR_KEY_DES)   {
		struct auth_update_component_info args;

		memset(&args, 0, sizeof(args));
		args.type = SC_CARDCTL_OBERTHUR_KEY_DES;
		args.data = (unsigned char *)buf;
		args.len = count;
		rv = auth_update_component(card, &args);
	}
	else   {
		rv = iso_ops->update_binary(card, offset, buf, count, 0);
	}

	LOG_FUNC_RETURN(card->ctx, rv);
}
