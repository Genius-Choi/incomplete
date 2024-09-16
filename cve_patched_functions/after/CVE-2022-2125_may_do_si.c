may_do_si()
{
    return curbuf->b_p_si
	&& !curbuf->b_p_cin
# ifdef FEAT_EVAL
	&& *curbuf->b_p_inde == NUL
# endif
	&& !p_paste;
}
