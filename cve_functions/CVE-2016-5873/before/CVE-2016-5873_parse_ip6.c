static const char *parse_ip6(struct parse_state *state, const char *ptr)
{
	const char *error = NULL, *end = state->ptr, *tmp = memchr(ptr, ']', end - ptr);
	TSRMLS_FETCH_FROM_CTX(state->ts);

	if (tmp) {
		size_t addrlen = tmp - ptr + 1;
		char buf[16], *addr = estrndup(ptr + 1, addrlen - 2);
		int rv = inet_pton(AF_INET6, addr, buf);

		if (rv == 1) {
			state->buffer[state->offset] = '[';
			state->url.host = &state->buffer[state->offset];
			inet_ntop(AF_INET6, buf, state->url.host + 1, state->maxlen - state->offset);
			state->offset += strlen(state->url.host);
			state->buffer[state->offset++] = ']';
			state->buffer[state->offset++] = 0;
			ptr = tmp + 1;
		} else if (rv == -1) {
			error = strerror(errno);
		} else {
			error = "unexpected '['";
		}
		efree(addr);
	} else {
		error = "expected ']'";
	}

	if (error) {
		php_error_docref(NULL TSRMLS_CC, E_WARNING, "Failed to parse hostinfo; %s", error);
		return NULL;
	}

	return ptr;
}
