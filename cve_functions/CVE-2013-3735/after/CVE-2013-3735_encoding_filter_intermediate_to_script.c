static size_t encoding_filter_intermediate_to_script(unsigned char **to, size_t *to_length, const unsigned char *from, size_t from_length TSRMLS_DC)
{
	return zend_multibyte_encoding_converter(to, to_length, from, from_length,
LANG_SCNG(script_encoding), zend_multibyte_encoding_utf8 TSRMLS_CC);
}
