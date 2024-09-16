static zval *row_dim_read(zval *object, zval *member, int type TSRMLS_DC)
{
	return row_prop_read(object, member, type, NULL TSRMLS_CC);
}
