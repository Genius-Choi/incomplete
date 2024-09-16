static union _zend_function *row_method_get(
	zval **object_pp,
	char *method_name, int method_len, const zend_literal *key TSRMLS_DC)
{
	zend_function *fbc;
	char *lc_method_name;

	lc_method_name = emalloc(method_len + 1);
	zend_str_tolower_copy(lc_method_name, method_name, method_len);

	if (zend_hash_find(&pdo_row_ce->function_table, lc_method_name, method_len+1, (void**)&fbc) == FAILURE) {
		efree(lc_method_name);
		return NULL;
	}

	efree(lc_method_name);
	return fbc;
}
