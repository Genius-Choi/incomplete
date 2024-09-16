static zend_class_entry *row_get_ce(const zval *object TSRMLS_DC)
{
	return pdo_row_ce;
}
