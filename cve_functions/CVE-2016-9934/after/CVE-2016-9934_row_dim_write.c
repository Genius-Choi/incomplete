static void row_dim_write(zval *object, zval *member, zval *value TSRMLS_DC)
{
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "This PDORow is not from a writable result set");
}
