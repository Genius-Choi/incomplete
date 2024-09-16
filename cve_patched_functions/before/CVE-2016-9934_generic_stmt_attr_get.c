static int generic_stmt_attr_get(pdo_stmt_t *stmt, zval *return_value, long attr)
{
	switch (attr) {
		case PDO_ATTR_EMULATE_PREPARES:
			RETVAL_BOOL(stmt->supports_placeholders == PDO_PLACEHOLDER_NONE);
			return 1;
	}
	return 0;
}
