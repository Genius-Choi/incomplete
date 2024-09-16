static int pdo_stmt_iter_valid(zend_object_iterator *iter TSRMLS_DC)
{
	struct php_pdo_iterator *I = (struct php_pdo_iterator*)iter->data;

	return I->fetch_ahead ? SUCCESS : FAILURE;
}
