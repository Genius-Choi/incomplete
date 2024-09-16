zend_object_value pdo_dbstmt_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	pdo_stmt_t *stmt;
	stmt = emalloc(sizeof(*stmt));
	memset(stmt, 0, sizeof(*stmt));
	zend_object_std_init(&stmt->std, ce TSRMLS_CC);
	object_properties_init(&stmt->std, ce);
	stmt->refcount = 1;

	retval.handle = zend_objects_store_put(stmt, (zend_objects_store_dtor_t)zend_objects_destroy_object, (zend_objects_free_object_storage_t)pdo_dbstmt_free_storage, (zend_objects_store_clone_t)dbstmt_clone_obj TSRMLS_CC);
	retval.handlers = &pdo_dbstmt_object_handlers;

	return retval;
}
