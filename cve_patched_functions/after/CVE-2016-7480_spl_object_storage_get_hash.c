static zend_string *spl_object_storage_get_hash(spl_SplObjectStorage *intern, zval *this, zval *obj) {
	if (intern->fptr_get_hash) {
		zval rv;
		zend_call_method_with_1_params(this, intern->std.ce, &intern->fptr_get_hash, "getHash", &rv, obj);
		if (!Z_ISUNDEF(rv)) {
			if (Z_TYPE(rv) == IS_STRING) {
				return Z_STR(rv);
			} else {
				zend_throw_exception(spl_ce_RuntimeException, "Hash needs to be a string", 0);

				zval_ptr_dtor(&rv);
				return NULL;
			}
		} else {
			return NULL;
		}
	} else {
		zend_string *hash = zend_string_alloc(sizeof(zend_object*), 0);
		memcpy(ZSTR_VAL(hash), (void*)&Z_OBJ_P(obj), sizeof(zend_object*));
		ZSTR_VAL(hash)[ZSTR_LEN(hash)] = '\0';
		return hash;
	}
}
