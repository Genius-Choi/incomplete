int highlight_string(zval *str, zend_syntax_highlighter_ini *syntax_highlighter_ini, char *str_name TSRMLS_DC)
{
	zend_lex_state original_lex_state;
	zval tmp = *str;

	str = &tmp;
	zval_copy_ctor(str);
	zend_save_lexical_state(&original_lex_state TSRMLS_CC);
	if (zend_prepare_string_for_scanning(str, str_name TSRMLS_CC)==FAILURE) {
		zend_restore_lexical_state(&original_lex_state TSRMLS_CC);
		return FAILURE;
	}
	BEGIN(INITIAL);
	zend_highlight(syntax_highlighter_ini TSRMLS_CC);
	if (SCNG(script_filtered)) {
		efree(SCNG(script_filtered));
		SCNG(script_filtered) = NULL;
	}
	zend_restore_lexical_state(&original_lex_state TSRMLS_CC);
	zval_dtor(str);
	return SUCCESS;
}
