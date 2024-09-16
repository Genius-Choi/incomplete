static void row_prop_write(zval *object, zval *member, zval *value, const zend_literal *key TSRMLS_DC)
{
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "This PDORow is not from a writable result set");
}
