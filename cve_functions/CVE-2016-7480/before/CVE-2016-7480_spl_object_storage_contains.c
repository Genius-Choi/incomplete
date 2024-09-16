int spl_object_storage_contains(spl_SplObjectStorage *intern, zval *this, zval *obj) /* {{{ */
{
	int found;
	zend_string *hash = spl_object_storage_get_hash(intern, this, obj);
	if (!hash) {
		return 0;
	}

	found = zend_hash_exists(&intern->storage, hash);
	spl_object_storage_free_hash(intern, hash);
	return found;
} /* }}} */
