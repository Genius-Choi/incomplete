get_indent_buf(buf_T *buf, linenr_T lnum)
{
# ifdef FEAT_VARTABS
    return get_indent_str_vtab(ml_get_buf(buf, lnum, FALSE),
			       (int)curbuf->b_p_ts, buf->b_p_vts_array, FALSE);
# else
    return get_indent_str(ml_get_buf(buf, lnum, FALSE), (int)buf->b_p_ts, FALSE);
# endif
}
