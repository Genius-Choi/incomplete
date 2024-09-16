php_http_url_t *php_http_url_copy(const php_http_url_t *url, zend_bool persistent)
{
	php_http_url_t *cpy;
	const char *end = NULL, *url_ptr = (const char *) url;
	char *cpy_ptr;

	end = MAX(url->scheme, end);
	end = MAX(url->pass, end);
	end = MAX(url->user, end);
	end = MAX(url->host, end);
	end = MAX(url->path, end);
	end = MAX(url->query, end);
	end = MAX(url->fragment, end);

	if (end) {
		end += strlen(end) + 1;
		cpy_ptr = pecalloc(1, end - url_ptr, persistent);
		cpy = (php_http_url_t *) cpy_ptr;

		memcpy(cpy_ptr + sizeof(*cpy), url_ptr + sizeof(*url), end - url_ptr - sizeof(*url));

		cpy->scheme = url->scheme ? cpy_ptr + (url->scheme - url_ptr) : NULL;
		cpy->pass = url->pass ? cpy_ptr + (url->pass - url_ptr) : NULL;
		cpy->user = url->user ? cpy_ptr + (url->user - url_ptr) : NULL;
		cpy->host = url->host ? cpy_ptr + (url->host - url_ptr) : NULL;
		cpy->path = url->path ? cpy_ptr + (url->path - url_ptr) : NULL;
		cpy->query = url->query ? cpy_ptr + (url->query - url_ptr) : NULL;
		cpy->fragment = url->fragment ? cpy_ptr + (url->fragment - url_ptr) : NULL;
	} else {
		cpy = ecalloc(1, sizeof(*url));
	}

	cpy->port = url->port;

	return cpy;
}
