static void php_free_gd_font(zend_rsrc_list_entry *rsrc TSRMLS_DC)
{
	gdFontPtr fp = (gdFontPtr) rsrc->ptr;

	if (fp->data) {
		efree(fp->data);
	}

	efree(fp);
}
