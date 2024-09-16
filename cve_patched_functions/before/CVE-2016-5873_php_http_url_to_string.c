char *php_http_url_to_string(const php_http_url_t *url, char **url_str, size_t *url_len, zend_bool persistent)
{
	php_http_buffer_t buf;

	php_http_buffer_init_ex(&buf, PHP_HTTP_BUFFER_DEFAULT_SIZE, persistent ?
			PHP_HTTP_BUFFER_INIT_PERSISTENT : 0);

	if (url->scheme && *url->scheme) {
		php_http_buffer_appendl(&buf, url->scheme);
		php_http_buffer_appends(&buf, "://");
	} else if ((url->user && *url->user) || (url->host && *url->host)) {
		php_http_buffer_appends(&buf, "//");
	}

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

	if (url->path && *url->path) {
		if (*url->path != '/') {
			php_http_buffer_appends(&buf, "/");
		}
		php_http_buffer_appendl(&buf, url->path);
	} else if (buf.used) {
		php_http_buffer_appends(&buf, "/");
	}

	if (url->query && *url->query) {
		php_http_buffer_appends(&buf, "?");
		php_http_buffer_appendl(&buf, url->query);
	}

	if (url->fragment && *url->fragment) {
		php_http_buffer_appends(&buf, "#");
		php_http_buffer_appendl(&buf, url->fragment);
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
