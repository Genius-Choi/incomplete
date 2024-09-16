authentic_update_blob(struct sc_context *ctx, unsigned tag, unsigned char *data, size_t data_len,
		unsigned char **blob, size_t *blob_size)
{
	unsigned char *pp = NULL;
	int offs = 0, sz;

	if (data_len == 0)
		return SC_SUCCESS;

	sz = data_len + 2;

	if (tag > 0xFF)
		sz++;

	if (data_len > 0x7F && data_len < 0x100)
		sz++;
	else if (data_len >= 0x100)
		sz += 2;

	pp = realloc(*blob, *blob_size + sz);
	if (!pp)
		LOG_FUNC_RETURN(ctx, SC_ERROR_OUT_OF_MEMORY);

	if (tag > 0xFF)
		*(pp + *blob_size + offs++) = (tag >> 8) & 0xFF;
	*(pp + *blob_size + offs++) = tag & 0xFF;

	if (data_len >= 0x100) {
		*(pp + *blob_size + offs++) = 0x82;
		*(pp + *blob_size + offs++) = (data_len >> 8) & 0xFF;
	}
	else if (data_len > 0x7F)   {
		*(pp + *blob_size + offs++) = 0x81;
	}
	*(pp + *blob_size + offs++) = data_len & 0xFF;

	memcpy(pp + *blob_size + offs, data, data_len);

	*blob_size += sz;
	*blob = pp;

	return SC_SUCCESS;
}
