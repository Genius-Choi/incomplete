PHP_FUNCTION(radius_demangle_mppe_key)
{
	radius_descriptor *raddesc;
	zval *z_radh;
	const void *mangled;
	unsigned char *buf;
	size_t dlen;
	int len, res;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rs", &z_radh, &mangled, &len) == FAILURE) {
		return;
	}

	ZEND_FETCH_RESOURCE(raddesc, radius_descriptor *, &z_radh, -1, "rad_handle", le_radius);

	buf = emalloc(len);
	res = rad_demangle_mppe_key(raddesc->radh, mangled, len, buf, &dlen);
	if (res == -1) {
		efree(buf);
		RETURN_FALSE;
	} else {
		RETVAL_STRINGL((char *) buf, dlen, 1);
		efree(buf);
		return;
	}
}
