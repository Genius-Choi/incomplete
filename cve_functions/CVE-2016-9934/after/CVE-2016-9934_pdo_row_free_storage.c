void pdo_row_free_storage(pdo_stmt_t *stmt TSRMLS_DC)
{
	if (stmt) {
		ZVAL_NULL(&stmt->lazy_object_ref);

		if (--stmt->refcount == 0) {
			free_statement(stmt TSRMLS_CC);
		}
	}
}
