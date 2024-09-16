static void row_prop_delete(zval *object, zval *offset, const zend_literal *key TSRMLS_DC)
{
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "Cannot delete properties from a PDORow");
}
