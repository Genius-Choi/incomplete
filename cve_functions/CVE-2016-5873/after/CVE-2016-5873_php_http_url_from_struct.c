php_http_url_t *php_http_url_from_struct(HashTable *ht)
{
	zval **e;
	php_http_buffer_t buf;

	php_http_buffer_init_ex(&buf, MAX(PHP_HTTP_BUFFER_DEFAULT_SIZE, sizeof(php_http_url_t)<<2), PHP_HTTP_BUFFER_INIT_PREALLOC);
	php_http_buffer_account(&buf, sizeof(php_http_url_t));
	memset(buf.data, 0, buf.used);

	if (SUCCESS == zend_hash_find(ht, "scheme", sizeof("scheme"), (void *) &e)) {
		zval *cpy = php_http_ztyp(IS_STRING, *e);
		url(buf)->scheme = &buf.data[buf.used];
		url_append(&buf, php_http_buffer_append(&buf, Z_STRVAL_P(cpy), Z_STRLEN_P(cpy) + 1));
		zval_ptr_dtor(&cpy);
	}
	if (SUCCESS == zend_hash_find(ht, "user", sizeof("user"), (void *) &e)) {
		zval *cpy = php_http_ztyp(IS_STRING, *e);
		url(buf)->user = &buf.data[buf.used];
		url_append(&buf, php_http_buffer_append(&buf, Z_STRVAL_P(cpy), Z_STRLEN_P(cpy) + 1));
		zval_ptr_dtor(&cpy);
	}
	if (SUCCESS == zend_hash_find(ht, "pass", sizeof("pass"), (void *) &e)) {
		zval *cpy = php_http_ztyp(IS_STRING, *e);
		url(buf)->pass = &buf.data[buf.used];
		url_append(&buf, php_http_buffer_append(&buf, Z_STRVAL_P(cpy), Z_STRLEN_P(cpy) + 1));
		zval_ptr_dtor(&cpy);
	}
	if (SUCCESS == zend_hash_find(ht, "host", sizeof("host"), (void *) &e)) {
		zval *cpy = php_http_ztyp(IS_STRING, *e);
		url(buf)->host = &buf.data[buf.used];
		url_append(&buf, php_http_buffer_append(&buf, Z_STRVAL_P(cpy), Z_STRLEN_P(cpy) + 1));
		zval_ptr_dtor(&cpy);
	}
	if (SUCCESS == zend_hash_find(ht, "port", sizeof("port"), (void *) &e)) {
		zval *cpy = php_http_ztyp(IS_LONG, *e);
		url(buf)->port = (unsigned short) Z_LVAL_P(cpy);
		zval_ptr_dtor(&cpy);
	}
	if (SUCCESS == zend_hash_find(ht, "path", sizeof("path"), (void *) &e)) {
		zval *cpy = php_http_ztyp(IS_STRING, *e);
		url(buf)->path = &buf.data[buf.used];
		url_append(&buf, php_http_buffer_append(&buf, Z_STRVAL_P(cpy), Z_STRLEN_P(cpy) + 1));
		zval_ptr_dtor(&cpy);
	}
	if (SUCCESS == zend_hash_find(ht, "query", sizeof("query"), (void *) &e)) {
		zval *cpy = php_http_ztyp(IS_STRING, *e);
		url(buf)->query = &buf.data[buf.used];
		url_append(&buf, php_http_buffer_append(&buf, Z_STRVAL_P(cpy), Z_STRLEN_P(cpy) + 1));
		zval_ptr_dtor(&cpy);
	}
	if (SUCCESS == zend_hash_find(ht, "fragment", sizeof("fragment"), (void *) &e)) {
		zval *cpy = php_http_ztyp(IS_STRING, *e);
		url(buf)->fragment = &buf.data[buf.used];
		url_append(&buf, php_http_buffer_append(&buf, Z_STRVAL_P(cpy), Z_STRLEN_P(cpy) + 1));
		zval_ptr_dtor(&cpy);
	}

	return url(buf);
}
