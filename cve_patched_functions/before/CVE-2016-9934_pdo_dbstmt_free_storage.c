void pdo_dbstmt_free_storage(pdo_stmt_t *stmt TSRMLS_DC)
{
	php_pdo_stmt_delref(stmt TSRMLS_CC);
}
