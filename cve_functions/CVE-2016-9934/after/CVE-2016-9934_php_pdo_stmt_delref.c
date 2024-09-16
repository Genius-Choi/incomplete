PDO_API void php_pdo_stmt_delref(pdo_stmt_t *stmt TSRMLS_DC)
{
	if (--stmt->refcount == 0) {
		free_statement(stmt TSRMLS_CC);
	}
}
