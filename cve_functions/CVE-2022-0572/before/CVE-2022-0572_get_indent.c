get_indent(void)
{
#ifdef FEAT_VARTABS
    return get_indent_str_vtab(ml_get_curline(), (int)curbuf->b_p_ts,
						 curbuf->b_p_vts_array, FALSE);
#else
    return get_indent_str(ml_get_curline(), (int)curbuf->b_p_ts, FALSE);
#endif
}
