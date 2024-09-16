static void pdo_stmt_iter_dtor(zend_object_iterator *iter TSRMLS_DC)
{
	struct php_pdo_iterator *I = (struct php_pdo_iterator*)iter->data;

	if (--I->stmt->refcount == 0) {
		free_statement(I->stmt TSRMLS_CC);
	}

	if (I->fetch_ahead) {
		zval_ptr_dtor(&I->fetch_ahead);
	}

	efree(I);
}
