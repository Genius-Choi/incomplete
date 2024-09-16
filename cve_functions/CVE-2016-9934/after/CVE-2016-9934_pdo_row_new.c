zend_object_value pdo_row_new(zend_class_entry *ce TSRMLS_DC)
{
	zend_object_value retval;

	retval.handle = zend_objects_store_put(NULL, (zend_objects_store_dtor_t)zend_objects_destroy_object, (zend_objects_free_object_storage_t)pdo_row_free_storage, NULL TSRMLS_CC);
	retval.handlers = &pdo_row_object_handlers;

	return retval;
}
