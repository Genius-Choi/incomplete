static ZEND_RESULT_CODE parse_uidn(struct parse_state *state)
{
	char *host_ptr;
	uint16_t *uhost_str, ahost_str[MAXHOSTNAMELEN], *ahost_ptr;
	size_t uhost_len, ahost_len;
	UErrorCode error = U_ZERO_ERROR;
	TSRMLS_FETCH_FROM_CTX(state->ts);

	if (state->flags & PHP_HTTP_URL_PARSE_MBUTF8) {
		if (SUCCESS != to_utf16(parse_mb_utf8, state->url.host, &uhost_str, &uhost_len TSRMLS_CC)) {
			return FAILURE;
		}
#ifdef PHP_HTTP_HAVE_WCHAR
	} else if (state->flags & PHP_HTTP_URL_PARSE_MBLOC) {
		if (SUCCESS != to_utf16(parse_mb_loc, state->url.host, &uhost_str, &uhost_len TSRMLS_CC)) {
			return FAILURE;
		}
#endif
	} else {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed to parse IDN; codepage not specified");
		return FAILURE;
	}

	ahost_len = uidna_IDNToASCII(uhost_str, uhost_len, ahost_str, MAXHOSTNAMELEN, 3, NULL, &error);
	efree(uhost_str);

	if (error != U_ZERO_ERROR) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed to parse IDN; ICU error %d", error);
		return FAILURE;
	}

	host_ptr = state->url.host;
	ahost_ptr = ahost_str;
	PHP_HTTP_DUFF(ahost_len, *host_ptr++ = *ahost_ptr++);

	*host_ptr = '\0';
	state->offset += host_ptr - state->url.host;

	return SUCCESS;
}
