fix_indent(void)
{
    if (p_paste)
	return;
    if (curbuf->b_p_lisp && curbuf->b_p_ai)
	fixthisline(get_lisp_indent);
    else
	if (cindent_on())
	    do_c_expr_indent();
}
