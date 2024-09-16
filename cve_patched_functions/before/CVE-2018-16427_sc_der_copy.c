sc_der_copy(sc_pkcs15_der_t *dst, const sc_pkcs15_der_t *src)
{
	if (!dst)
		return SC_ERROR_INVALID_ARGUMENTS;
	memset(dst, 0, sizeof(*dst));
	if (src->len) {
		dst->value = malloc(src->len);
		if (!dst->value)
			return SC_ERROR_OUT_OF_MEMORY;
		dst->len = src->len;
		memcpy(dst->value, src->value, src->len);
	}
	return SC_SUCCESS;
}
