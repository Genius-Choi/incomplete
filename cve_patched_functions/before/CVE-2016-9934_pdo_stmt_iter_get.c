zend_object_iterator *pdo_stmt_iter_get(zend_class_entry *ce, zval *object, int by_ref TSRMLS_DC)
{
	pdo_stmt_t *stmt = (pdo_stmt_t*)zend_object_store_get_object(object TSRMLS_CC);
	struct php_pdo_iterator *I;

	if (by_ref) {
		zend_error(E_ERROR, "An iterator cannot be used with foreach by reference");
	}

	I = ecalloc(1, sizeof(*I));
	I->iter.funcs = &pdo_stmt_iter_funcs;
	I->iter.data = I;
	I->stmt = stmt;
	stmt->refcount++;

	MAKE_STD_ZVAL(I->fetch_ahead);
	if (!do_fetch(I->stmt, TRUE, I->fetch_ahead, PDO_FETCH_USE_DEFAULT,
			PDO_FETCH_ORI_NEXT, 0, 0 TSRMLS_CC)) {
		PDO_HANDLE_STMT_ERR();
		I->key = (ulong)-1;
		FREE_ZVAL(I->fetch_ahead);
		I->fetch_ahead = NULL;
	}

	return &I->iter;
}
