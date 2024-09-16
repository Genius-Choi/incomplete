PDO_API void php_pdo_stmt_addref(pdo_stmt_t *stmt TSRMLS_DC)
{
	stmt->refcount++;
}
