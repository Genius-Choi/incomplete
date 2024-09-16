php_http_url_t *php_http_url_parse_authority(const char *str, size_t len, unsigned flags TSRMLS_DC)
{
	size_t maxlen = 3 * len;
	struct parse_state *state = ecalloc(1, sizeof(*state) + maxlen);

	state->end = str + len;
	state->ptr = str;
	state->flags = flags;
	state->maxlen = maxlen;
	TSRMLS_SET_CTX(state->ts);

	if (!(state->ptr = parse_authority(state))) {
		efree(state);
		return NULL;
	}

	if (state->ptr != state->end) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING,
				"Failed to parse URL authority, unexpected character at pos %u in '%s'",
				(unsigned) (state->ptr - str), str);
		efree(state);
		return NULL;
	}

	return (php_http_url_t *) state;
}
