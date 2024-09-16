get_indent_lnum(linenr_T lnum)
{
#ifdef FEAT_VARTABS
    return get_indent_str_vtab(ml_get(lnum), (int)curbuf->b_p_ts,
						 curbuf->b_p_vts_array, FALSE);
#else
    return get_indent_str(ml_get(lnum), (int)curbuf->b_p_ts, FALSE);
#endif
}
