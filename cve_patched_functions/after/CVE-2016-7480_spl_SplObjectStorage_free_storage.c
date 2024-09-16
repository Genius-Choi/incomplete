void spl_SplObjectStorage_free_storage(zend_object *object) /* {{{ */
{
	spl_SplObjectStorage *intern = spl_object_storage_from_obj(object);

	zend_object_std_dtor(&intern->std);

	zend_hash_destroy(&intern->storage);

	if (intern->gcdata != NULL) {
		efree(intern->gcdata);
	}

} /* }}} */
