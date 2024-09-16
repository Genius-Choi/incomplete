void php_http_url_free(php_http_url_t **url)
{
	if (*url) {
		efree(*url);
		*url = NULL;
	}
}
