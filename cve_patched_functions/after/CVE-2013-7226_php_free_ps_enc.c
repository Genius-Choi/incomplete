static void php_free_ps_enc(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	char **enc = (char **) rsrc->ptr;

	T1_DeleteEncoding(enc);
}
