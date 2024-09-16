static void php_free_ps_font(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	int *font = (int *) rsrc->ptr;

	T1_DeleteFont(*font);
	efree(font);
}
