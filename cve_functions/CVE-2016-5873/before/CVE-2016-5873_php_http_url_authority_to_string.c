char *php_http_url_authority_to_string(const php_http_url_t *url, char **url_str, size_t *url_len)
{
	php_http_buffer_t buf;

	php_http_buffer_init(&buf);

	if (url->user && *url->user) {
		php_http_buffer_appendl(&buf, url->user);
		if (url->pass && *url->pass) {
			php_http_buffer_appends(&buf, ":");
			php_http_buffer_appendl(&buf, url->pass);
		}
		php_http_buffer_appends(&buf, "@");
	}

	if (url->host && *url->host) {
		php_http_buffer_appendl(&buf, url->host);
		if (url->port) {
			php_http_buffer_appendf(&buf, ":%hu", url->port);
		}
	}

	php_http_buffer_shrink(&buf);
	php_http_buffer_fix(&buf);

	if (url_len) {
		*url_len = buf.used;
	}

	if (url_str) {
		*url_str = buf.data;
	}

	return buf.data;
}
