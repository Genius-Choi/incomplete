static int row_get_classname(const zval *object, const char **class_name, zend_uint *class_name_len, int parent TSRMLS_DC)
{
	if (parent) {
		return FAILURE;
	} else {
		*class_name = estrndup("PDORow", sizeof("PDORow")-1);
		*class_name_len = sizeof("PDORow")-1;
		return SUCCESS;
	}
}
