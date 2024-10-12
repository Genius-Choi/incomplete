PHP_FUNCTION(radius_cvt_addr)
{
	const void *data;
	char *addr_dot;
	int len;
	struct in_addr addr;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &data, &len) == FAILURE) {
		return;
	}

	addr = rad_cvt_addr(data);
	addr_dot = inet_ntoa(addr);
	RETURN_STRINGL(addr_dot, strlen(addr_dot), 1);
}
