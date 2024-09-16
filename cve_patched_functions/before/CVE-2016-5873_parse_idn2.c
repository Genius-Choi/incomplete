static ZEND_RESULT_CODE parse_idn2(struct parse_state *state, size_t prev_len)
{
	char *idn = NULL;
	int rv = -1;
	TSRMLS_FETCH_FROM_CTX(state->ts);

	if (state->flags & PHP_HTTP_URL_PARSE_MBUTF8) {
		rv = idn2_lookup_u8((const unsigned char *) state->url.host, (unsigned char **) &idn, IDN2_NFC_INPUT);
	}
#	ifdef PHP_HTTP_HAVE_WCHAR
	else if (state->flags & PHP_HTTP_URL_PARSE_MBLOC) {
		rv = idn2_lookup_ul(state->url.host, &idn, 0);
	}
#	endif
	if (rv != IDN2_OK) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed to parse IDN; %s", idn2_strerror(rv));
		return FAILURE;
	} else {
		size_t idnlen = strlen(idn);
		memcpy(state->url.host, idn, idnlen + 1);
		free(idn);
		state->offset += idnlen - prev_len;
		return SUCCESS;
	}
}
