static void dbstmt_prop_write(zval *object, zval *member, zval *value, const zend_literal *key TSRMLS_DC)
{
	pdo_stmt_t * stmt = (pdo_stmt_t *) zend_object_store_get_object(object TSRMLS_CC);

	convert_to_string(member);

	if(strcmp(Z_STRVAL_P(member), "queryString") == 0) {
		pdo_raise_impl_error(stmt->dbh, stmt, "HY000", "property queryString is read only" TSRMLS_CC);
	} else {
		std_object_handlers.write_property(object, member, value, key TSRMLS_CC);
	}
}
