static PHP_METHOD(PDOStatement, __sleep)
{
	zend_throw_exception_ex(php_pdo_get_exception(), 0 TSRMLS_CC, "You cannot serialize or unserialize PDOStatement instances");
}
