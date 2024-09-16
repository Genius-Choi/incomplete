static int pdo_row_serialize(zval *object, unsigned char **buffer, zend_uint *buf_len, zend_serialize_data *data TSRMLS_DC)
{
	php_error_docref(NULL TSRMLS_CC, E_WARNING, "PDORow instances may not be serialized");
	return FAILURE;
}
