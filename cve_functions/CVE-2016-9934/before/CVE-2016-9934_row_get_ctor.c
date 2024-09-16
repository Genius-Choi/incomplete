static union _zend_function *row_get_ctor(zval *object TSRMLS_DC)
{
	static zend_internal_function ctor = {0};

	ctor.type = ZEND_INTERNAL_FUNCTION;
	ctor.function_name = "__construct";
	ctor.scope = pdo_row_ce;
	ctor.handler = ZEND_FN(dbstmt_constructor);
	ctor.fn_flags = ZEND_ACC_PUBLIC;

	return (union _zend_function*)&ctor;
}
