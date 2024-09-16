static void _yy_push_state(int new_state TSRMLS_DC)
{
	zend_stack_push(&SCNG(state_stack), (void *) &YYGETCONDITION(), sizeof(int));
	YYSETCONDITION(new_state);
}
